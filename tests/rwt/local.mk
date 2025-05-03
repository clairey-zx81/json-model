# special case for localizations
l10n.dcheck.out: l10n.model.json
	$(JMC.cmd) -v -DO --no-code --true ./$< english.model.json français.model.json > $@
	echo "# localized models" >> $@
	$(JMC.cmd) -v -DO --no-code --true ./english.model.json en_00.model.json >> $@
	$(JMC.cmd) -v -DO --no-code --true ./français.model.json fr_00.model.json >> $@

# special case for localizations
l10n.scheck.out: l10n.model.json
	$(JMC.cmd) -v -SO --no-code --true ./$< english.model.json français.model.json > $@
	echo "# localized models" >> $@
	$(JMC.cmd) -v -SO --no-code --true ./english.model.json en_00.model.json >> $@
	$(JMC.cmd) -v -SO --no-code --true ./français.model.json fr_00.model.json >> $@

l10n.jcheck.out: l10n.schema.json
	$(JSC) $< english.model.json français.model.json > $@
	# echo "# localized models" >> $@
	# $(JSC) english.schema.json en_00.model.json >> $@
	# $(JSC) français.schema.json fr_00.model.json >> $@

# external references are not supported
E.KO    = \
    $(wildcard json-schema-*-fuzzy.model.json) \
    $(wildcard json-schema-*-nesting.model.json) \
    json-schema-draft-tighter-loose

# skip errors
E.root  = \
    $(E.KO:%.model.json=%) \
    json-model-preprocessed \
    json-model-moschin \
    json-model-v2-en \
    english \
    français \
    openapi-310 \
    openapi-310-models \
    mrg_02 \
    obj_03 \
    obj_04 \
    scope_1 \
    hello2 \
    hello3 \
    scp_01

$(E.root:%=%.jcheck.out):
	touch $@
