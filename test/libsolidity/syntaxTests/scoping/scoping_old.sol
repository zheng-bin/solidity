contract test {
    function f() pure public {
        x = 4;
        uint256 x = 2;
    }
}
// ----
// DeclarationError: (55-56): Undeclared identifier. Did you mean to declare "x" earlier?
