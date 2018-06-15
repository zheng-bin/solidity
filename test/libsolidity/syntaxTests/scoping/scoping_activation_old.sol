contract test {
    function f() pure public {
        x = 3;
        uint x;
    }
}
// ----
// DeclarationError: (55-56): Undeclared identifier. Did you mean to declare "x" earlier?
