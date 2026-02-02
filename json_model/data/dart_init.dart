// dart_init.dart
class GlobalState {
  static bool initializer = false;
}

Function? CHECK_FUNCTION_NAME_fun(String name) {
  return CHECK_FUNCTION_NAME_map[name];
}


void CHECK_FUNCTION_NAME_init() {
  if (!GlobalState.initializer){
    GlobalState.initializer = true;
  }
CODE_BLOCK
}