interface I {
    function f() external virtual;
}
contract C is I {
    function f() public override {
    }
}
// ----
// Warning: (18-48): Interface functions are implicitly "virtual"
