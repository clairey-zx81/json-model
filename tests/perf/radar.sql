WITH
   BestPerf AS (
    SELECT name, MIN(run) AS best
    FROM CumulatedPerf
    GROUP BY 1
  ),
  RelativePerf AS (
    SELECT tool, name, CASE WHEN run IS NOT NULL AND run <> 0 THEN best / run ELSE 0.0 END AS perf
    FROM CumulatedPerf
    LEFT JOIN BestPerf USING (name)
    GROUP BY 1, 2
    ORDER BY 1, 2
  ),
  ArrayPerf AS (
    SELECT tool, json_group_array(perf) AS data -- OVER (ORDER BY name) AS data
    FROM RelativePerf
    GROUP BY tool
  ),
  PerToolPerf AS (
    SELECT
      json_object(
        'label', label,
        'data', JSON(data)
      ) AS obj
    FROM ArrayPerf
    JOIN Labels USING (tool)
    ORDER BY tool
  )
SELECT json_group_array(JSON(obj)) -- OVER (ORDER BY obj->>'label')
FROM PerToolPerf;
