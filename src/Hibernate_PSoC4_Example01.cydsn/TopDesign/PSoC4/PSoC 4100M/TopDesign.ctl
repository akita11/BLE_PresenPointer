-- =============================================================================
-- The following directives assign pins to the locations specific for the
-- CY8CKIT-044 kit.
-- =============================================================================

-- === UART ===
attribute port_location of \UART:rx(0)\ : label is "PORT(7,0)";
attribute port_location of \UART:tx(0)\ : label is "PORT(7,1)";

-- === I2C ===
attribute port_location of \I2C:scl(0)\ : label is "PORT(4,0)";
attribute port_location of \I2C:sda(0)\ : label is "PORT(4,1)";

-- === RGB LED ===
attribute port_location of LED_Status(0) : label is "PORT(0,6)"; -- RED LED
attribute port_location of LED_Mode(0) : label is "PORT(2,6)"; -- GREEN LED
attribute port_location of REPLACE_WITH_ACTUAL_PIN_NAME(0) : label is "PORT(6,5)"; -- BLUE LED

-- === USER SWITCH ===
attribute port_location of Pin_Sw(0) : label is "PORT(0,7)";