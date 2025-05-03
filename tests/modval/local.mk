# special case for the meta model
MODEL   = ../../models/json-model.model.json

# all possibly models
OK.model  = $(F.model) $(wildcard ../bads/_*.model.json ../../models/*.model.json)
KO.model  = $(F.bads)

F.Xcheck    = model.dcheck.out model.scheck.out model.jcheck.out

.PHONY: check.models
check.models: $(F.Xcheck)

F.gen += $(F.Xcheck) model.schema.json

model.dcheck.out: $(OK.model) $(KO.model)
	$(JMC.cmd) -v -DO --no-code --true $(MODEL) $(OK.model) | sort > $@
	$(JMC.cmd) -v -DO --no-code --false $(MODEL) $(KO.model) | sort >> $@

# special case for the meta model
model.scheck.out: $(OK.model) $(KO.model)
	$(JMC.cmd) -v -SO --no-code --true $(MODEL) $(OK.model) | sort > $@
	$(JMC.cmd) -v -SO --no-code --false $(MODEL) $(KO.model) | sort >> $@

model.schema.json: $(MODEL)
	$(JMC.cmd) -v -EO $(MODEL) > $@

# special cases
model.jcheck.out: model.schema.json $(OK.model)
	shopt -s nullglob
	$(JSC) model.schema.json $(OK.model) | sort > $@
