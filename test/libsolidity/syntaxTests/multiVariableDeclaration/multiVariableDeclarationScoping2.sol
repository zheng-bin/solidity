contract C {
  function f() internal {
    {
      (uint a, uint b, uint c) = (a, b, c);
    }
  }
} 
// ----
// DeclarationError: (79-80): Undeclared identifier. Did you mean to declare "a" earlier?
// DeclarationError: (82-83): Undeclared identifier. Did you mean to declare "b" earlier?
// DeclarationError: (85-86): Undeclared identifier. Did you mean to declare "c" earlier?
