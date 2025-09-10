#! /bin/bash

LOOP=${1:-1000}

./perf_run.sh $LOOP draft-04 &
./perf_run.sh $LOOP geojson &
./perf_run.sh $LOOP openapi &
./perf_run.sh $LOOP omnisharp &
./perf_run.sh $LOOP ansible-meta aws-cdk babelrc &
./perf_run.sh $LOOP clang-format cmake-presets code-climate &
./perf_run.sh $LOOP cql2 cspell cypress &
./perf_run.sh $LOOP deno dependabot &
./perf_run.sh $LOOP fabric-mod gitpod-configuration &
./perf_run.sh $LOOP helm-chart-lock importmap jasmine &
./perf_run.sh $LOOP jsconfig jshintrc krakend &
./perf_run.sh $LOOP lazygit lerna nest-cli &
./perf_run.sh $LOOP pre-commit-hooks pulumi semantic-release &
./perf_run.sh $LOOP stale stylecop tmuxinator &
./perf_run.sh $LOOP ui5 ui5-manifest unreal-engine-uproject &
./perf_run.sh $LOOP vercel yamllint &
