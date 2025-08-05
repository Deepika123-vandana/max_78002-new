README for tests folder
folder structure
gpio
  |-> inc
    |-> gpio_test.h
  |-> src
    |-> gpio_test.c
flash
i2c
accelerometer
gyroscope

/*
*EXAMPLE <driver>_test.c for gpio
*gpio_test.c --> Tests for GPIO driver
*/
test_gpio_set()
{
  gpio_set(PORT,PIN,VAL); // define these in header file

  if(gpio_get(2,0) == 0)
    return PASS;
  else
    return FAIL;
}
test_gpio_get()
{
  gpio_set(2,0,0);

  if(gpio_get(2,0) == 0)
    return PASS;
  else
    return FAIL;
}
test_gpio_toggle()
{

}
