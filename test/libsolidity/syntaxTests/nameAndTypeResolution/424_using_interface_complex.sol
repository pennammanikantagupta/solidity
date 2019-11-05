interface I {
    event A();
    function f() external virtual;
    function g() external;
    fallback() external;
}
abstract contract C is I {
    function f() public override {
    }
}
// ----
// Warning: (33-63): Interface functions are implicitly "virtual"
