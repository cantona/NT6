//Cracked by Kafei
// /d/shenlong/sgjob/sgjob50000.c

// inherit SKILL;

inherit F_CLEAN_UP;

mapping *sgjobs = ({
        ([      "sgjob":          "太極十三勢",
                "sgjob_type":           "尋",
                "exp_bonus":             150,
                "pot_bonus":             40,
                "score":                 2
        ]),

        ([      "sgjob":          "舊竹片",
                "sgjob_type":           "尋",
                "exp_bonus":             150,
                "pot_bonus":             40,
                "score":                 2
        ]),

        ([      "sgjob":          "薄絹",
                "sgjob_type":           "尋",
                "exp_bonus":             150,
                "pot_bonus":             40,
                "score":                 2
        ]),

        ([      "sgjob":          "石板",
                "sgjob_type":           "尋",
                "exp_bonus":             50,
                "pot_bonus":             10,
                "score":                 1
        ]),

        ([      "sgjob":          "紫霞秘笈",
                "sgjob_type":           "尋",
                "exp_bonus":             200,
                "pot_bonus":             50,
                "score":                 2
        ]),

        ([      "sgjob":          "杖法圖解",
                "sgjob_type":           "尋",
                "exp_bonus":             150,
                "pot_bonus":             40,
                "score":                 2
        ]),

        ([      "sgjob":          "碧磷針",
                "sgjob_type":           "尋",
                "exp_bonus":             160,
                "pot_bonus":             40,
                "score":                 2
        ]),

        ([      "sgjob":          "化屍粉",
                "sgjob_type":           "尋",
                "exp_bonus":             160,
                "pot_bonus":             40,
                "score":                 2
        ]),

        ([      "sgjob":          "香",
                "sgjob_type":           "尋",
                "exp_bonus":             60,
                "pot_bonus":             10,
                "score":                 1
        ]),

        ([      "sgjob":          "煉心彈",
                "sgjob_type":           "尋",
                "exp_bonus":             60,
                "pot_bonus":             10,
                "score":                 1
        ]),

        ([      "sgjob":          "蒙汗藥",
                "sgjob_type":           "尋",
                "exp_bonus":             30,
                "pot_bonus":             5,
                "score":                 1
        ]),

        ([      "sgjob":          "蛇杖",
                "sgjob_type":           "尋",
                "exp_bonus":            120,
                "pot_bonus":             30,
                "score":                 2
        ]),

        ([      "sgjob":          "清心散",
                "sgjob_type":           "尋",
                "exp_bonus":            100,
                "pot_bonus":             30,
                "score":                 1
        ]),

        ([      "sgjob":          "FORCEJOIN",
        ]),

        ([      "sgjob":          "FORCEJOIN",
        ]),

        ([      "sgjob":          "FORCEJOIN",
        ]),

        ([      "sgjob":          "FORCEJOIN",
        ]),

        ([      "sgjob":          "FORCEJOIN",
        ]),

        ([      "sgjob":          "FORCEJOIN",
        ]),

        ([      "sgjob":          "FORCEJOIN",
        ]),

        ([      "sgjob":          "FORCEJOIN",
        ]),

        ([      "sgjob":          "FORCEJOIN",
        ]),

        ([      "sgjob":          "FORCEJOIN",
        ]),

        ([      "sgjob":          "FORCEJOIN",
        ]),

        ([      "sgjob":          "FORCEJOIN",
        ]),

        ([      "sgjob":          "FORCEJOIN",
        ]),

        ([      "sgjob":          "FORCEJOIN",
        ]),

        ([      "sgjob":          "FORCEJOIN",
        ]),

        ([      "sgjob":          "FORCEJOIN",
        ]),
        ([      "sgjob":          "FORCEJOIN",
        ]),

        ([      "sgjob":          "FORCEJOIN",
        ]),

        ([      "sgjob":          "FORCEJOIN",
        ]),

        ([      "sgjob":          "FORCEJOIN",
        ]),

        ([      "sgjob":          "FORCEJOIN",
        ]),

        ([      "sgjob":          "FORCEJOIN",
        ]),

        ([      "sgjob":          "FORCEJOIN",
        ]),

        ([      "sgjob":          "FORCEJOIN",
        ]),

        ([      "sgjob":          "PK",
        ]),

        ([      "sgjob":          "PK",
        ]),

        ([      "sgjob":          "PK",
        ]),
});

void create() { seteuid(getuid()); }

mapping query_sgjob()
{
        return sgjobs[random(sizeof(sgjobs))];
}
