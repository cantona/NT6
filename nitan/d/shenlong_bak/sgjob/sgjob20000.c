//Cracked by Kafei
// /d/shenlong/sgjob/sgjob20000.c

// inherit SKILL;

inherit F_CLEAN_UP;

mapping *sgjobs = ({
        ([      "sgjob":          "道德經",
                "sgjob_type":           "尋",
                "exp_bonus":             10,
                "pot_bonus":             3,
                "score":                 1
        ]),

        ([      "sgjob":          "『星宿毒經』",
                "sgjob_type":           "尋",
                "exp_bonus":             30,
                "pot_bonus":             8,
                "score":                 1
        ]),

        ([      "sgjob":          "持世陀羅尼經",
                "sgjob_type":           "尋",
                "exp_bonus":             40,
                "pot_bonus":             10,
                "score":                 1
        ]),

        ([      "sgjob":          "鐵八卦",
                "sgjob_type":           "尋",
                "exp_bonus":             120,
                "pot_bonus":             30,
                "score":                 2
        ]),

        ([      "sgjob":          "華山劍譜",
                "sgjob_type":           "尋",
                "exp_bonus":             150,
                "pot_bonus":             40,
                "score":                 2
        ]),

        ([      "sgjob":          "唐詩選輯",
                "sgjob_type":           "尋",
                "exp_bonus":             150,
                "pot_bonus":             40,
                "score":                 2
        ]),

        ([      "sgjob":          "胡家刀法殘篇",
                "sgjob_type":           "尋",
                "exp_bonus":             250,
                "pot_bonus":             60,
                "score":                 2
        ]),

        ([      "sgjob":          "少林英雄令",
                "sgjob_type":           "尋",
                "exp_bonus":             120,
                "pot_bonus":             30,
                "score":                 1
        ]),

        ([      "sgjob":          "罰惡令",
                "sgjob_type":           "尋",
                "exp_bonus":             100,
                "pot_bonus":             25,
                "score":                 2
        ]),

        ([      "sgjob":          "賞善令",
                "sgjob_type":           "尋",
                "exp_bonus":             100,
                "pot_bonus":             25,
                "score":                 2
        ]),

        ([      "sgjob":          "正氣訣訣譜上卷",
                "sgjob_type":           "尋",
                "exp_bonus":             30,
                "pot_bonus":             8,
                "score":                 1
        ]),

        ([      "sgjob":          "正氣訣訣譜下卷",
                "sgjob_type":           "尋",
                "exp_bonus":             30,
                "pot_bonus":             8,
                "score":                 1
        ]),

        ([      "sgjob":          "紫氤吟訣譜上卷",
                "sgjob_type":           "尋",
                "exp_bonus":             30,
                "pot_bonus":             8,
                "score":                 1
        ]),

        ([      "sgjob":          "紫氤吟訣譜下卷",
                "sgjob_type":           "尋",
                "exp_bonus":             30,
                "pot_bonus":             8,
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

        ([      "sgjob":          "PK",
        ]),

        ([      "sgjob":          "PK",
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

