
fn main() {
  let language = tree_sitter_dust::language();
  let mut parser = tree_sitter::Parser::new();
  parser.set_language(language).unwrap();

  let source = r#"
    flex name = "hello";
  "#;

  let tree = match parser.parse(source, None) {
    Some(tree) => tree,
    None => {
      panic!("Unable to parse!");
    }
  };

  dbg!(tree.root_node().to_sexp());
}
