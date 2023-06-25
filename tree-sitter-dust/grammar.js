module.exports = grammar({
  name: 'dust',

  rules: {
    source_file: $ => repeat($._statement),

    _statement: $ => choice(
      $.assignment,
    ),

    _END_OF_STATEMENT: $ => choice(';'),

    expression: $ => choice(
      $.identifier,
      $.number,
      $.string,
      $.boolean,
    ),

    assignment: $ => seq(
      "flex",
      $.identifier,
      "=",
      $.expression,
      $._END_OF_STATEMENT,
    ),

    identifier: $ => /[a-zA-Z_][a-zA-Z0-9_]*/,
    number: $ => /\d+/,
    string: $ => /"[^"]*"/,
    boolean: $ => choice("true", "false"),
  }
})