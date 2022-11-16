PI Estimation
=============
This is a simple project aiming to estimate PI through multi-threading.

How to run
----------
```
$ make
$ ./pi -p [precision]
```

Implementation
--------------
1. Calculate each digit independently. (`PIDigitEstimator.h/get_nth_digit_of_pi()`)
2. Run the above program through thread pooling with [# of hardward thread] threads. (`main.cpp/estimate_pi()`)
3. Test the correctness of each digit `i` by checking the overlap between digit `i` and `i-1`. (`main.cpp/max_precision()`)
4. Print out the value of pi along with the calculation time. (`main.cpp/print_pi(), main.cpp/main()`)

Reference
---------
The file `PIDigitEstimator.h` is mostly copied from [Bellard's Website](https://bellard.org/pi/pi1.c).
