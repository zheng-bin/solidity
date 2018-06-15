contract test {
    function f() pure public {
        uint a = a;
    }
}
// ----
// DeclarationError: (64-65): Undeclared identifier. Did you mean to declare "a" earlier?
