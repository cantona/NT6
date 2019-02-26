#include <ansi.h>

mapping *quest = ({
        ([
                "id" :    "yue er",
                "name" :  "月兒",
                "bonus":  75,
                "type":   "殺",
        ]),
        ([
                "id" :    "cloth",
                "name" :  "布衣",
                "bonus":  50,
                "type":   "尋",
        ]),
        ([
                "id" :    "cloth",
                "name" :  "布衣",
                "bonus":  60,
                "type":   "徵",
                "object": "/d/city/obj/cloth.c",
        ]),
        ([
                "id" :    "cloth",
                "name" :  "布衣",
                "bonus":  60,
                "type":   "送",
                "object": "/d/city/obj/cloth.c",
        ]),
});

mapping query_quest()
{
        return quest[random(sizeof(quest))];
}
