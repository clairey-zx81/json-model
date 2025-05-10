typedef struct {
  const char * property;
  check_fun_t val_check;
} check_prop_t;

static int prop_cmp(const check_prop_t *e1, const check_prop_t *e2)
{
  return strcmp(e1->property, e2->property);
}

static check_fun_t
check_prop_find(const char * name, const check_prop_t *props, int nprops)
{
  check_prop_t searched = (check_prop_t) { name, NULL };
  check_prop_t *entry = (check_prop_t *)
    bsearch(&searched, props, nprops, sizeof(check_prop_t), (cmp_fun_t) prop_cmp);
  return entry ? entry->val_check : NULL;
}
