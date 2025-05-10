typedef struct {
  string property;
  check_fun_t val_check;
} check_prop_t;

static check_prop_t *
check_prop_find(const string name, const check_prop_t *props, int nprops)
{
  return (check_prop_t *) bsearch(name, props, nprops, sizeof(string), (cmp_fun_t) strcmp);
}
