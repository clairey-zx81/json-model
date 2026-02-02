library json_model;

import 'dart:convert';

//
// Regular Expression Helper
//
class RX {
  final RegExp _re;
  RX(String pattern, String flags)
      : _re = RegExp(
          pattern,
          caseSensitive: !flags.contains('i'),
          multiLine: flags.contains('m'),
        );

  bool hasMatch(String s) => _re.hasMatch(s);
  Match? firstMatch(String s) => _re.firstMatch(s);
}

//
// Date - Time Helper
//

// Helper: Check if a year is a leap year
bool _isLeapYear(int year) {
  return (year % 4 == 0) && ((year % 100 != 0) || (year % 400 == 0));
}

// Helper: Get max days in a month
int _daysInMonth(int year, int month) {
  if (month == 2) {
    return _isLeapYear(year) ? 29 : 28;
  }
  // April, June, September, November have 30 days
  if ([4, 6, 9, 11].contains(month)) {
    return 30;
  }
  // All others have 31
  return 31;
}

//
// Validation Helpers
//

bool jm_is_valid_uuid(dynamic val) {
  if (val is! String) return false;
  // Standard UUID regex (8-4-4-4-12 hex digits)
  final re = RegExp(
    r'^[0-9a-fA-F]{8}-[0-9a-fA-F]{4}-[0-9a-fA-F]{4}-[0-9a-fA-F]{4}-[0-9a-fA-F]{12}$',
  );
  return re.hasMatch(val);
}

bool jm_is_valid_date(dynamic val, List<dynamic>? path, List<dynamic>? rep) {
  if (val is! String) return false;

  final re = RegExp(r'^(\d{4})-(\d{2})-(\d{2})$');
  final match = re.firstMatch(val);
  if (match == null) return false;

  int year = int.parse(match.group(1)!);
  int month = int.parse(match.group(2)!);
  int day = int.parse(match.group(3)!);

  //  Month Range
  if (month < 1 || month > 12) return false;

  // Days in Month (including leap years)
  if (day < 1 || day > _daysInMonth(year, month)) return false;

  return true;
}

bool jm_is_valid_time(dynamic val, List<dynamic>? path, List<dynamic>? rep) {
  if (val is! String) return false;

  // REGEX BREAKDOWN:
  // 1. ^T?                         -> Optional 'T' prefix (e.g. "T12...")
  // 2. (\d{2})                     -> Group 1: Hours
  // 3. (:?)                        -> Group 2: Separator (Colon or Empty)
  // 4. (\d{2})                     -> Group 3: Minutes
  // 5. \2                          -> Backreference to Group 2.
  //                                   (If Group 2 was ':', this must be ':'. If empty, this must be empty.)
  // 6. (\d{2})                     -> Group 4: Seconds
  // 7. (?:\.\d+)?                  -> Optional Fractional seconds (.123)
  // 8. (?:Z|[+-]\d{2}(?::?\d{2})?)? -> Optional Timezone (Z, +01, +0100, -01:00)
  final re = RegExp(
      r'^T?(\d{2})(:?)(\d{2})\2(\d{2})(?:\.\d+)?(?:Z|[+-]\d{2}(?::?\d{2})?)?$');

  final match = re.firstMatch(val);
  if (match == null) return false;

  // Extract components using the specific groups
  int hour = int.parse(match.group(1)!);
  int minute = int.parse(match.group(3)!); // Skip group 2 (separator)
  int second = int.parse(match.group(4)!);

  // Logical Validation
  if (hour < 0 || hour > 23) return false;
  if (minute < 0 || minute > 59) return false;
  if (second < 0 || second > 59) return false;

  return true;
}

bool jm_is_valid_datetime(
    dynamic val, List<dynamic>? path, List<dynamic>? rep) {
  if (val is! String) return false;

  // REGEX BREAKDOWN:
  // 1. ^(\d{4}-\d{2}-\d{2})       -> Group 1: Date (YYYY-MM-DD)
  // 2. [ T]                       -> Separator: Space or 'T'
  // 3. (\d{2}:\d{2}:\d{2}(?:\.\d+)?) -> Group 2: Time (HH:MM:SS.mmm)
  // 4. (?:Z|[+-]\d{2}(?::?\d{2})?)?  -> Non-capturing Group: Timezone
  //    Matches: Z, +01, -01, +0130, -01:30, +0100
  final re = RegExp(
      r'^(\d{4}-\d{2}-\d{2})[ T](\d{2}:\d{2}:\d{2}(?:\.\d+)?)(?:Z|[+-]\d{2}(?::?\d{2})?)?$');
  final match = re.firstMatch(val);

  if (match == null) return false;

  String datePart = match.group(1)!;
  String timePart = match.group(2)!;

  if (!jm_is_valid_date(datePart, null, null)) return false;
  if (!jm_is_valid_time(timePart, null, null)) return false;

  return true;
}

bool jm_is_valid_regex(dynamic val, bool extended) {
  if (val is! String) return false;
  try {
    RegExp(val);
    return true;
  } catch (e) {
    return false;
  }
}

bool jm_is_valid_url(dynamic val) {
  if (val is! String) return false;
  final uri = Uri.tryParse(val);
  return uri != null &&
      (uri.scheme == 'http' || uri.scheme == 'https' || uri.scheme == 'ftp');
}

bool jm_is_valid_email(dynamic val) {
  if (val is! String) return false;
  // Basic HTML5 email regex
  final re = RegExp(
    r"^[a-zA-Z0-9.!#$%&'*+/=?^_`{|}~-]+@[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?(?:\.[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?)*$",
  );
  return re.hasMatch(val);
}

bool jm_is_valid_json(dynamic val) {
  if (val is! String) return false;
  try {
    jsonDecode(val);
    return true;
  } catch (e) {
    return false;
  }
}

int jm_any_len(dynamic val) {
  if (val is String) return val.length;
  if (val is List) return val.length;
  if (val is Map) return val.length;
  return 0;
}

bool jm_array_is_unique(dynamic val, List<dynamic>? path, List<dynamic>? rep) {
  // 1. Must be a List (handles null, string, numbers etc.)
  if (val is! List) return false;

  // 2. O(N^2) Deep comparison to detect duplicates
  for (int i = 0; i < val.length; i++) {
    for (int j = i + 1; j < val.length; j++) {
      if (_jm_deep_eq(val[i], val[j])) {
        // Duplicate found
        if (rep != null) rep.add(["Array elements are not unique", path]);
        return false;
      }
    }
  }
  return true;
}

// Helper: Recursive Deep Equality with Strict Type Checking
bool _jm_deep_eq(dynamic a, dynamic b) {
  // 1. Identity Check
  if (identical(a, b)) return true;

  // 2. Strict Type Check (Crucial for 0 vs 0.0)
  // In Dart, 0 == 0.0 is true, but runtimeTypes (int vs double) differ.
  if (a.runtimeType != b.runtimeType) return false;

  // 3. Lists
  if (a is List) {
    if (a.length != b.length) return false;
    for (int i = 0; i < a.length; i++) {
      if (!_jm_deep_eq(a[i], b[i])) return false;
    }
    return true;
  }

  // 4. Maps (JSON Objects)
  if (a is Map) {
    if (a.length != b.length) return false;
    for (final key in a.keys) {
      if (!b.containsKey(key)) return false;
      if (!_jm_deep_eq(a[key], b[key])) return false;
    }
    return true;
  }

  // 5. Primitives (String, bool, etc.)
  return a == b;
}

bool jm_array_is_unique_efficient(
    dynamic val, List<dynamic>? path, List<dynamic>? rep) {
  if (val is! List) return false;
  final uniqueSet = val.toSet();

  if (uniqueSet.length != val.length) {
    if (rep != null) rep.add(["Array elements are not unique", path]);
    return false;
  }
  return true;
}

bool jm_check_constraint(
  dynamic val,
  String op,
  dynamic vop,
  List<dynamic>? path,
  List<dynamic>? rep,
) {
  bool result = false;

  // Handle numbers
  if (val is num && vop is num) {
    switch (op) {
      case '==':
        result = val == vop;
        break;
      case '!=':
        result = val != vop;
        break;
      case '<':
        result = val < vop;
        break;
      case '<=':
        result = val <= vop;
        break;
      case '>':
        result = val > vop;
        break;
      case '>=':
        result = val >= vop;
        break;
      default:
        result = false;
    }
  }
  // Handle Strings (Length or Equality)
  else if (val is String) {
    if (op == 'match') {
      // vop is expected to be a Regex pattern string
      result = RegExp(vop.toString()).hasMatch(val);
    } else if (vop is num) {
      // Length comparison
      int len = val.length;
      switch (op) {
        case '==':
          result = len == vop;
          break;
        case '!=':
          result = len != vop;
          break;
        case '<':
          result = len < vop;
          break;
        case '<=':
          result = len <= vop;
          break;
        case '>':
          result = len > vop;
          break;
        case '>=':
          result = len >= vop;
          break;
      }
    } else {
      // String equality
      result = (val == vop);
    }
  }
  // Handle Arrays/Maps (Length)
  else if ((val is List || val is Map) && vop is num) {
    int len = (val is List) ? val.length : (val as Map).length;
    switch (op) {
      case '==':
        result = len == vop;
        break;
      case '!=':
        result = len != vop;
        break;
      case '<':
        result = len < vop;
        break;
      case '<=':
        result = len <= vop;
        break;
      case '>':
        result = len > vop;
        break;
      case '>=':
        result = len >= vop;
        break;
    }
  }

  if (!result && rep != null) {
    rep.add(["Constraint failed: $val $op $vop", path]);
  }
  return result;
}
