#ifndef IDENTIFIER_H
#define IDENTIFIER_H

#include <stddef.h>
#include <stdint.h>

/// @brief This was stolen from treesitter generate's parser, when asked to match the following regex `/[_\p{L}\p{Emoji}][_0-9\p{L}\p{Emoji}]*/u`
/// @param c The codepoint to check
/// @return true if the codepoint is '_', 0-9, part of the Letter unicode category or part of the Emoji unicode category
inline bool is_valid_identifier_char(int32_t c) {
  return (c < 9742
    ? (c < 3520
      ? (c < 2544
        ? (c < 1749
          ? (c < 886
            ? (c < 186
              ? (c < '_'
                ? (c < '0'
                  ? (c < '*'
                    ? c == '#'
                    : c <= '*')
                  : (c <= '9' || (c >= 'A' && c <= 'Z')))
                : (c <= '_' || (c < 174
                  ? (c < 169
                    ? (c >= 'a' && c <= 'z')
                    : c <= 170)
                  : (c <= 174 || c == 181))))
              : (c <= 186 || (c < 736
                ? (c < 248
                  ? (c < 216
                    ? (c >= 192 && c <= 214)
                    : c <= 246)
                  : (c <= 705 || (c >= 710 && c <= 721)))
                : (c <= 740 || (c < 750
                  ? c == 748
                  : (c <= 750 || (c >= 880 && c <= 884)))))))
            : (c <= 887 || (c < 1162
              ? (c < 908
                ? (c < 902
                  ? (c < 895
                    ? (c >= 890 && c <= 893)
                    : c <= 895)
                  : (c <= 902 || (c >= 904 && c <= 906)))
                : (c <= 908 || (c < 931
                  ? (c >= 910 && c <= 929)
                  : (c <= 1013 || (c >= 1015 && c <= 1153)))))
              : (c <= 1327 || (c < 1519
                ? (c < 1376
                  ? (c < 1369
                    ? (c >= 1329 && c <= 1366)
                    : c <= 1369)
                  : (c <= 1416 || (c >= 1488 && c <= 1514)))
                : (c <= 1522 || (c < 1646
                  ? (c >= 1568 && c <= 1610)
                  : (c <= 1647 || (c >= 1649 && c <= 1747)))))))))
          : (c <= 1749 || (c < 2160
            ? (c < 1994
              ? (c < 1808
                ? (c < 1786
                  ? (c < 1774
                    ? (c >= 1765 && c <= 1766)
                    : c <= 1775)
                  : (c <= 1788 || c == 1791))
                : (c <= 1808 || (c < 1869
                  ? (c >= 1810 && c <= 1839)
                  : (c <= 1957 || c == 1969))))
              : (c <= 2026 || (c < 2084
                ? (c < 2048
                  ? (c < 2042
                    ? (c >= 2036 && c <= 2037)
                    : c <= 2042)
                  : (c <= 2069 || c == 2074))
                : (c <= 2084 || (c < 2112
                  ? c == 2088
                  : (c <= 2136 || (c >= 2144 && c <= 2154)))))))
            : (c <= 2183 || (c < 2447
              ? (c < 2384
                ? (c < 2308
                  ? (c < 2208
                    ? (c >= 2185 && c <= 2190)
                    : c <= 2249)
                  : (c <= 2361 || c == 2365))
                : (c <= 2384 || (c < 2417
                  ? (c >= 2392 && c <= 2401)
                  : (c <= 2432 || (c >= 2437 && c <= 2444)))))
              : (c <= 2448 || (c < 2493
                ? (c < 2482
                  ? (c < 2474
                    ? (c >= 2451 && c <= 2472)
                    : c <= 2480)
                  : (c <= 2482 || (c >= 2486 && c <= 2489)))
                : (c <= 2493 || (c < 2524
                  ? c == 2510
                  : (c <= 2525 || (c >= 2527 && c <= 2529)))))))))))
        : (c <= 2545 || (c < 2972
          ? (c < 2768
            ? (c < 2654
              ? (c < 2602
                ? (c < 2575
                  ? (c < 2565
                    ? c == 2556
                    : c <= 2570)
                  : (c <= 2576 || (c >= 2579 && c <= 2600)))
                : (c <= 2608 || (c < 2616
                  ? (c < 2613
                    ? (c >= 2610 && c <= 2611)
                    : c <= 2614)
                  : (c <= 2617 || (c >= 2649 && c <= 2652)))))
              : (c <= 2654 || (c < 2730
                ? (c < 2703
                  ? (c < 2693
                    ? (c >= 2674 && c <= 2676)
                    : c <= 2701)
                  : (c <= 2705 || (c >= 2707 && c <= 2728)))
                : (c <= 2736 || (c < 2741
                  ? (c >= 2738 && c <= 2739)
                  : (c <= 2745 || c == 2749))))))
            : (c <= 2768 || (c < 2877
              ? (c < 2835
                ? (c < 2821
                  ? (c < 2809
                    ? (c >= 2784 && c <= 2785)
                    : c <= 2809)
                  : (c <= 2828 || (c >= 2831 && c <= 2832)))
                : (c <= 2856 || (c < 2866
                  ? (c >= 2858 && c <= 2864)
                  : (c <= 2867 || (c >= 2869 && c <= 2873)))))
              : (c <= 2877 || (c < 2949
                ? (c < 2929
                  ? (c < 2911
                    ? (c >= 2908 && c <= 2909)
                    : c <= 2913)
                  : (c <= 2929 || c == 2947))
                : (c <= 2954 || (c < 2962
                  ? (c >= 2958 && c <= 2960)
                  : (c <= 2965 || (c >= 2969 && c <= 2970)))))))))
          : (c <= 2972 || (c < 3242
            ? (c < 3114
              ? (c < 3024
                ? (c < 2984
                  ? (c < 2979
                    ? (c >= 2974 && c <= 2975)
                    : c <= 2980)
                  : (c <= 2986 || (c >= 2990 && c <= 3001)))
                : (c <= 3024 || (c < 3086
                  ? (c >= 3077 && c <= 3084)
                  : (c <= 3088 || (c >= 3090 && c <= 3112)))))
              : (c <= 3129 || (c < 3200
                ? (c < 3165
                  ? (c < 3160
                    ? c == 3133
                    : c <= 3162)
                  : (c <= 3165 || (c >= 3168 && c <= 3169)))
                : (c <= 3200 || (c < 3214
                  ? (c >= 3205 && c <= 3212)
                  : (c <= 3216 || (c >= 3218 && c <= 3240)))))))
            : (c <= 3251 || (c < 3389
              ? (c < 3313
                ? (c < 3293
                  ? (c < 3261
                    ? (c >= 3253 && c <= 3257)
                    : c <= 3261)
                  : (c <= 3294 || (c >= 3296 && c <= 3297)))
                : (c <= 3314 || (c < 3342
                  ? (c >= 3332 && c <= 3340)
                  : (c <= 3344 || (c >= 3346 && c <= 3386)))))
              : (c <= 3389 || (c < 3461
                ? (c < 3423
                  ? (c < 3412
                    ? c == 3406
                    : c <= 3414)
                  : (c <= 3425 || (c >= 3450 && c <= 3455)))
                : (c <= 3478 || (c < 3507
                  ? (c >= 3482 && c <= 3505)
                  : (c <= 3515 || c == 3517))))))))))))
      : (c <= 3526 || (c < 6576
        ? (c < 4704
          ? (c < 4096
            ? (c < 3762
              ? (c < 3716
                ? (c < 3648
                  ? (c < 3634
                    ? (c >= 3585 && c <= 3632)
                    : c <= 3635)
                  : (c <= 3654 || (c >= 3713 && c <= 3714)))
                : (c <= 3716 || (c < 3749
                  ? (c < 3724
                    ? (c >= 3718 && c <= 3722)
                    : c <= 3747)
                  : (c <= 3749 || (c >= 3751 && c <= 3760)))))
              : (c <= 3763 || (c < 3840
                ? (c < 3782
                  ? (c < 3776
                    ? c == 3773
                    : c <= 3780)
                  : (c <= 3782 || (c >= 3804 && c <= 3807)))
                : (c <= 3840 || (c < 3913
                  ? (c >= 3904 && c <= 3911)
                  : (c <= 3948 || (c >= 3976 && c <= 3980)))))))
            : (c <= 4138 || (c < 4256
              ? (c < 4197
                ? (c < 4186
                  ? (c < 4176
                    ? c == 4159
                    : c <= 4181)
                  : (c <= 4189 || c == 4193))
                : (c <= 4198 || (c < 4213
                  ? (c >= 4206 && c <= 4208)
                  : (c <= 4225 || c == 4238))))
              : (c <= 4293 || (c < 4682
                ? (c < 4304
                  ? (c < 4301
                    ? c == 4295
                    : c <= 4301)
                  : (c <= 4346 || (c >= 4348 && c <= 4680)))
                : (c <= 4685 || (c < 4696
                  ? (c >= 4688 && c <= 4694)
                  : (c <= 4696 || (c >= 4698 && c <= 4701)))))))))
          : (c <= 4744 || (c < 5873
            ? (c < 4882
              ? (c < 4800
                ? (c < 4786
                  ? (c < 4752
                    ? (c >= 4746 && c <= 4749)
                    : c <= 4784)
                  : (c <= 4789 || (c >= 4792 && c <= 4798)))
                : (c <= 4800 || (c < 4808
                  ? (c >= 4802 && c <= 4805)
                  : (c <= 4822 || (c >= 4824 && c <= 4880)))))
              : (c <= 4885 || (c < 5121
                ? (c < 5024
                  ? (c < 4992
                    ? (c >= 4888 && c <= 4954)
                    : c <= 5007)
                  : (c <= 5109 || (c >= 5112 && c <= 5117)))
                : (c <= 5740 || (c < 5761
                  ? (c >= 5743 && c <= 5759)
                  : (c <= 5786 || (c >= 5792 && c <= 5866)))))))
            : (c <= 5880 || (c < 6176
              ? (c < 5998
                ? (c < 5952
                  ? (c < 5919
                    ? (c >= 5888 && c <= 5905)
                    : c <= 5937)
                  : (c <= 5969 || (c >= 5984 && c <= 5996)))
                : (c <= 6000 || (c < 6103
                  ? (c >= 6016 && c <= 6067)
                  : (c <= 6103 || c == 6108))))
              : (c <= 6264 || (c < 6400
                ? (c < 6314
                  ? (c < 6279
                    ? (c >= 6272 && c <= 6276)
                    : c <= 6312)
                  : (c <= 6314 || (c >= 6320 && c <= 6389)))
                : (c <= 6430 || (c < 6512
                  ? (c >= 6480 && c <= 6509)
                  : (c <= 6516 || (c >= 6528 && c <= 6571)))))))))))
        : (c <= 6601 || (c < 8160
          ? (c < 7418
            ? (c < 7168
              ? (c < 6981
                ? (c < 6823
                  ? (c < 6688
                    ? (c >= 6656 && c <= 6678)
                    : c <= 6740)
                  : (c <= 6823 || (c >= 6917 && c <= 6963)))
                : (c <= 6988 || (c < 7086
                  ? (c >= 7043 && c <= 7072)
                  : (c <= 7087 || (c >= 7098 && c <= 7141)))))
              : (c <= 7203 || (c < 7357
                ? (c < 7296
                  ? (c < 7258
                    ? (c >= 7245 && c <= 7247)
                    : c <= 7293)
                  : (c <= 7304 || (c >= 7312 && c <= 7354)))
                : (c <= 7359 || (c < 7406
                  ? (c >= 7401 && c <= 7404)
                  : (c <= 7411 || (c >= 7413 && c <= 7414)))))))
            : (c <= 7418 || (c < 8029
              ? (c < 8008
                ? (c < 7960
                  ? (c < 7680
                    ? (c >= 7424 && c <= 7615)
                    : c <= 7957)
                  : (c <= 7965 || (c >= 7968 && c <= 8005)))
                : (c <= 8013 || (c < 8025
                  ? (c >= 8016 && c <= 8023)
                  : (c <= 8025 || c == 8027))))
              : (c <= 8029 || (c < 8130
                ? (c < 8118
                  ? (c < 8064
                    ? (c >= 8031 && c <= 8061)
                    : c <= 8116)
                  : (c <= 8124 || c == 8126))
                : (c <= 8132 || (c < 8144
                  ? (c >= 8134 && c <= 8140)
                  : (c <= 8147 || (c >= 8150 && c <= 8155)))))))))
          : (c <= 8172 || (c < 8495
            ? (c < 8455
              ? (c < 8305
                ? (c < 8252
                  ? (c < 8182
                    ? (c >= 8178 && c <= 8180)
                    : c <= 8188)
                  : (c <= 8252 || c == 8265))
                : (c <= 8305 || (c < 8336
                  ? c == 8319
                  : (c <= 8348 || c == 8450))))
              : (c <= 8455 || (c < 8484
                ? (c < 8473
                  ? (c < 8469
                    ? (c >= 8458 && c <= 8467)
                    : c <= 8469)
                  : (c <= 8477 || c == 8482))
                : (c <= 8484 || (c < 8488
                  ? c == 8486
                  : (c <= 8488 || (c >= 8490 && c <= 8493)))))))
            : (c <= 8505 || (c < 9167
              ? (c < 8596
                ? (c < 8526
                  ? (c < 8517
                    ? (c >= 8508 && c <= 8511)
                    : c <= 8521)
                  : (c <= 8526 || (c >= 8579 && c <= 8580)))
                : (c <= 8601 || (c < 8986
                  ? (c >= 8617 && c <= 8618)
                  : (c <= 8987 || c == 9000))))
              : (c <= 9167 || (c < 9654
                ? (c < 9410
                  ? (c < 9208
                    ? (c >= 9193 && c <= 9203)
                    : c <= 9210)
                  : (c <= 9410 || (c >= 9642 && c <= 9643)))
                : (c <= 9654 || (c < 9723
                  ? c == 9664
                  : (c <= 9726 || (c >= 9728 && c <= 9732)))))))))))))))
    : (c <= 9742 || (c < 43793
      ? (c < 11680
        ? (c < 9986
          ? (c < 9854
            ? (c < 9784
              ? (c < 9760
                ? (c < 9752
                  ? (c < 9748
                    ? c == 9745
                    : c <= 9749)
                  : (c <= 9752 || c == 9757))
                : (c <= 9760 || (c < 9770
                  ? (c < 9766
                    ? (c >= 9762 && c <= 9763)
                    : c <= 9766)
                  : (c <= 9770 || (c >= 9774 && c <= 9775)))))
              : (c <= 9786 || (c < 9827
                ? (c < 9800
                  ? (c < 9794
                    ? c == 9792
                    : c <= 9794)
                  : (c <= 9811 || (c >= 9823 && c <= 9824)))
                : (c <= 9827 || (c < 9832
                  ? (c >= 9829 && c <= 9830)
                  : (c <= 9832 || c == 9851))))))
            : (c <= 9855 || (c < 9924
              ? (c < 9895
                ? (c < 9883
                  ? (c < 9881
                    ? (c >= 9874 && c <= 9879)
                    : c <= 9881)
                  : (c <= 9884 || (c >= 9888 && c <= 9889)))
                : (c <= 9895 || (c < 9904
                  ? (c >= 9898 && c <= 9899)
                  : (c <= 9905 || (c >= 9917 && c <= 9918)))))
              : (c <= 9925 || (c < 9961
                ? (c < 9937
                  ? (c < 9934
                    ? c == 9928
                    : c <= 9935)
                  : (c <= 9937 || (c >= 9939 && c <= 9940)))
                : (c <= 9962 || (c < 9975
                  ? (c >= 9968 && c <= 9973)
                  : (c <= 9978 || c == 9981))))))))
          : (c <= 9986 || (c < 10133
            ? (c < 10024
              ? (c < 10004
                ? (c < 9999
                  ? (c < 9992
                    ? c == 9989
                    : c <= 9997)
                  : (c <= 9999 || c == 10002))
                : (c <= 10004 || (c < 10013
                  ? c == 10006
                  : (c <= 10013 || c == 10017))))
              : (c <= 10024 || (c < 10062
                ? (c < 10055
                  ? (c < 10052
                    ? (c >= 10035 && c <= 10036)
                    : c <= 10052)
                  : (c <= 10055 || c == 10060))
                : (c <= 10062 || (c < 10071
                  ? (c >= 10067 && c <= 10069)
                  : (c <= 10071 || (c >= 10083 && c <= 10084)))))))
            : (c <= 10135 || (c < 11264
              ? (c < 11013
                ? (c < 10175
                  ? (c < 10160
                    ? c == 10145
                    : c <= 10160)
                  : (c <= 10175 || (c >= 10548 && c <= 10549)))
                : (c <= 11015 || (c < 11088
                  ? (c >= 11035 && c <= 11036)
                  : (c <= 11088 || c == 11093))))
              : (c <= 11492 || (c < 11565
                ? (c < 11520
                  ? (c < 11506
                    ? (c >= 11499 && c <= 11502)
                    : c <= 11507)
                  : (c <= 11557 || c == 11559))
                : (c <= 11565 || (c < 11631
                  ? (c >= 11568 && c <= 11623)
                  : (c <= 11631 || (c >= 11648 && c <= 11670)))))))))))
        : (c <= 11686 || (c < 42960
          ? (c < 12704
            ? (c < 12293
              ? (c < 11720
                ? (c < 11704
                  ? (c < 11696
                    ? (c >= 11688 && c <= 11694)
                    : c <= 11702)
                  : (c <= 11710 || (c >= 11712 && c <= 11718)))
                : (c <= 11726 || (c < 11736
                  ? (c >= 11728 && c <= 11734)
                  : (c <= 11742 || c == 11823))))
              : (c <= 12294 || (c < 12449
                ? (c < 12353
                  ? (c < 12347
                    ? (c >= 12336 && c <= 12341)
                    : c <= 12349)
                  : (c <= 12438 || (c >= 12445 && c <= 12447)))
                : (c <= 12538 || (c < 12549
                  ? (c >= 12540 && c <= 12543)
                  : (c <= 12591 || (c >= 12593 && c <= 12686)))))))
            : (c <= 12735 || (c < 42240
              ? (c < 19903
                ? (c < 12953
                  ? (c < 12951
                    ? (c >= 12784 && c <= 12799)
                    : c <= 12951)
                  : (c <= 12953 || c == 13312))
                : (c <= 19903 || (c < 40959
                  ? c == 19968
                  : (c <= 42124 || (c >= 42192 && c <= 42237)))))
              : (c <= 42508 || (c < 42656
                ? (c < 42560
                  ? (c < 42538
                    ? (c >= 42512 && c <= 42527)
                    : c <= 42539)
                  : (c <= 42606 || (c >= 42623 && c <= 42653)))
                : (c <= 42725 || (c < 42786
                  ? (c >= 42775 && c <= 42783)
                  : (c <= 42888 || (c >= 42891 && c <= 42954)))))))))
          : (c <= 42961 || (c < 43494
            ? (c < 43250
              ? (c < 43015
                ? (c < 42994
                  ? (c < 42965
                    ? c == 42963
                    : c <= 42969)
                  : (c <= 43009 || (c >= 43011 && c <= 43013)))
                : (c <= 43018 || (c < 43072
                  ? (c >= 43020 && c <= 43042)
                  : (c <= 43123 || (c >= 43138 && c <= 43187)))))
              : (c <= 43255 || (c < 43360
                ? (c < 43274
                  ? (c < 43261
                    ? c == 43259
                    : c <= 43262)
                  : (c <= 43301 || (c >= 43312 && c <= 43334)))
                : (c <= 43388 || (c < 43471
                  ? (c >= 43396 && c <= 43442)
                  : (c <= 43471 || (c >= 43488 && c <= 43492)))))))
            : (c <= 43503 || (c < 43701
              ? (c < 43616
                ? (c < 43584
                  ? (c < 43520
                    ? (c >= 43514 && c <= 43518)
                    : c <= 43560)
                  : (c <= 43586 || (c >= 43588 && c <= 43595)))
                : (c <= 43638 || (c < 43646
                  ? c == 43642
                  : (c <= 43695 || c == 43697))))
              : (c <= 43702 || (c < 43744
                ? (c < 43714
                  ? (c < 43712
                    ? (c >= 43705 && c <= 43709)
                    : c <= 43712)
                  : (c <= 43714 || (c >= 43739 && c <= 43741)))
                : (c <= 43754 || (c < 43777
                  ? (c >= 43762 && c <= 43764)
                  : (c <= 43782 || (c >= 43785 && c <= 43790)))))))))))))
      : (c <= 43798 || (c < 67639
        ? (c < 65576
          ? (c < 64320
            ? (c < 63744
              ? (c < 43888
                ? (c < 43824
                  ? (c < 43816
                    ? (c >= 43808 && c <= 43814)
                    : c <= 43822)
                  : (c <= 43866 || (c >= 43868 && c <= 43881)))
                : (c <= 44002 || (c < 55216
                  ? (c < 55203
                    ? c == 44032
                    : c <= 55203)
                  : (c <= 55238 || (c >= 55243 && c <= 55291)))))
              : (c <= 64109 || (c < 64287
                ? (c < 64275
                  ? (c < 64256
                    ? (c >= 64112 && c <= 64217)
                    : c <= 64262)
                  : (c <= 64279 || c == 64285))
                : (c <= 64296 || (c < 64312
                  ? (c >= 64298 && c <= 64310)
                  : (c <= 64316 || c == 64318))))))
            : (c <= 64321 || (c < 65313
              ? (c < 64914
                ? (c < 64467
                  ? (c < 64326
                    ? (c >= 64323 && c <= 64324)
                    : c <= 64433)
                  : (c <= 64829 || (c >= 64848 && c <= 64911)))
                : (c <= 64967 || (c < 65136
                  ? (c >= 65008 && c <= 65019)
                  : (c <= 65140 || (c >= 65142 && c <= 65276)))))
              : (c <= 65338 || (c < 65490
                ? (c < 65474
                  ? (c < 65382
                    ? (c >= 65345 && c <= 65370)
                    : c <= 65470)
                  : (c <= 65479 || (c >= 65482 && c <= 65487)))
                : (c <= 65495 || (c < 65536
                  ? (c >= 65498 && c <= 65500)
                  : (c <= 65547 || (c >= 65549 && c <= 65574)))))))))
          : (c <= 65594 || (c < 66864
            ? (c < 66370
              ? (c < 66176
                ? (c < 65616
                  ? (c < 65599
                    ? (c >= 65596 && c <= 65597)
                    : c <= 65613)
                  : (c <= 65629 || (c >= 65664 && c <= 65786)))
                : (c <= 66204 || (c < 66304
                  ? (c >= 66208 && c <= 66256)
                  : (c <= 66335 || (c >= 66349 && c <= 66368)))))
              : (c <= 66377 || (c < 66560
                ? (c < 66464
                  ? (c < 66432
                    ? (c >= 66384 && c <= 66421)
                    : c <= 66461)
                  : (c <= 66499 || (c >= 66504 && c <= 66511)))
                : (c <= 66717 || (c < 66776
                  ? (c >= 66736 && c <= 66771)
                  : (c <= 66811 || (c >= 66816 && c <= 66855)))))))
            : (c <= 66915 || (c < 67072
              ? (c < 66967
                ? (c < 66956
                  ? (c < 66940
                    ? (c >= 66928 && c <= 66938)
                    : c <= 66954)
                  : (c <= 66962 || (c >= 66964 && c <= 66965)))
                : (c <= 66977 || (c < 66995
                  ? (c >= 66979 && c <= 66993)
                  : (c <= 67001 || (c >= 67003 && c <= 67004)))))
              : (c <= 67382 || (c < 67506
                ? (c < 67456
                  ? (c < 67424
                    ? (c >= 67392 && c <= 67413)
                    : c <= 67431)
                  : (c <= 67461 || (c >= 67463 && c <= 67504)))
                : (c <= 67514 || (c < 67592
                  ? (c >= 67584 && c <= 67589)
                  : (c <= 67592 || (c >= 67594 && c <= 67637)))))))))))
        : (c <= 67640 || (c < 128405
          ? (c < 127535
            ? (c < 126980
              ? (c < 67808
                ? (c < 67680
                  ? (c < 67647
                    ? c == 67644
                    : c <= 67669)
                  : (c <= 67702 || (c >= 67712 && c <= 67742)))
                : (c <= 67826 || (c < 67840
                  ? (c >= 67828 && c <= 67829)
                  : (c <= 67861 || (c >= 67872 && c <= 67883)))))
              : (c <= 126980 || (c < 127377
                ? (c < 127358
                  ? (c < 127344
                    ? c == 127183
                    : c <= 127345)
                  : (c <= 127359 || c == 127374))
                : (c <= 127386 || (c < 127489
                  ? (c >= 127462 && c <= 127487)
                  : (c <= 127490 || c == 127514))))))
            : (c <= 127535 || (c < 127991
              ? (c < 127894
                ? (c < 127744
                  ? (c < 127568
                    ? (c >= 127538 && c <= 127546)
                    : c <= 127569)
                  : (c <= 127777 || (c >= 127780 && c <= 127891)))
                : (c <= 127895 || (c < 127902
                  ? (c >= 127897 && c <= 127899)
                  : (c <= 127984 || (c >= 127987 && c <= 127989)))))
              : (c <= 128253 || (c < 128371
                ? (c < 128336
                  ? (c < 128329
                    ? (c >= 128255 && c <= 128317)
                    : c <= 128334)
                  : (c <= 128359 || (c >= 128367 && c <= 128368)))
                : (c <= 128378 || (c < 128394
                  ? c == 128391
                  : (c <= 128397 || c == 128400))))))))
          : (c <= 128406 || (c < 128745
            ? (c < 128483
              ? (c < 128450
                ? (c < 128433
                  ? (c < 128424
                    ? (c >= 128420 && c <= 128421)
                    : c <= 128424)
                  : (c <= 128434 || c == 128444))
                : (c <= 128452 || (c < 128476
                  ? (c >= 128465 && c <= 128467)
                  : (c <= 128478 || c == 128481))))
              : (c <= 128483 || (c < 128640
                ? (c < 128499
                  ? (c < 128495
                    ? c == 128488
                    : c <= 128495)
                  : (c <= 128499 || (c >= 128506 && c <= 128591)))
                : (c <= 128709 || (c < 128725
                  ? (c >= 128715 && c <= 128722)
                  : (c <= 128727 || (c >= 128733 && c <= 128741)))))))
            : (c <= 128745 || (c < 129648
              ? (c < 129008
                ? (c < 128755
                  ? (c < 128752
                    ? (c >= 128747 && c <= 128748)
                    : c <= 128752)
                  : (c <= 128764 || (c >= 128992 && c <= 129003)))
                : (c <= 129008 || (c < 129340
                  ? (c >= 129292 && c <= 129338)
                  : (c <= 129349 || (c >= 129351 && c <= 129535)))))
              : (c <= 129652 || (c < 129728
                ? (c < 129680
                  ? (c < 129664
                    ? (c >= 129656 && c <= 129660)
                    : c <= 129670)
                  : (c <= 129708 || (c >= 129712 && c <= 129722)))
                : (c <= 129733 || (c < 129760
                  ? (c >= 129744 && c <= 129753)
                  : (c <= 129767 || (c >= 129776 && c <= 129782)))))))))))))))));
}

typedef struct {
  size_t start_byte;
  size_t line;
  size_t start_column;
  size_t length;
  const char* text;
} Identifier_t;

#endif
