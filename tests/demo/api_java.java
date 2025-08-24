import json_model.*;

public class api_java {
  static public void main(String[] args) throws JSON.Exception {
    JSON json = new GSON();
    ModelChecker person = new Person();
    person.init(json);
    Object hobbes = json.fromJSON("{\"name\": \"Hobbes\", \"birth\": \"2020-07-29\"}");
    System.out.println("hobbes is a person: " + person.get("").call(hobbes));
  }
}
