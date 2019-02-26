#include <ansi.h>
#include <room.h>
inherit ROOM;

string look_duilian();

void create()
{
        set("short", HIB "【輪迴道】" NOR);
        set("long", HIB @LONG

                    輪         回         道

    輪迴道上寒氣森森的，青石鋪設的地面滿是灰塵。四周一片寂靜，偶
爾傳來幾聲冤魂野鬼的慟哭聲，使氣氛顯得格外的恐怖詭異。你的面前是
一座雄偉的大殿，殿堂的高匾上寫着「輪迴司」三個大字，匾下有一幅殘
缺不全的對聯(duilian)。輪迴司巨大厚實的銅門(door)緊緊關閉着。

LONG NOR );

        set("exits", ([
                "enter" : __DIR__"lunhuisi",
                "west"  : __DIR__"jimiesi",
        ]));

        set("item_desc", ([
                "door" : YEL "一扇厚厚的銅門，上面佈滿了蛛網和灰塵。\n" NOR,
                "duilian" :       (: look_duilian :),
        ]));

        create_door("enter", YEL "銅門" NOR, "out", DOOR_CLOSED);
        set("no_magic", 1);
        setup();
}

string look_duilian()
{
        return
        RED "\n"
        "             ※※※※※※※            ※※※※※※※\n"
        "             ※※※※※※※            ※※※※※※※\n"
        "             ※※      ※※            ※※      ※※\n"
        "             ※※" NOR + HIW "　天　" NOR + RED "※※            ※※" NOR + HIW "  血  " NOR + RED "※※\n"
        "             ※※　 　 ※※            ※※      ※※\n"
        "             ※※" NOR + HIW "  地  " NOR + RED "※※            ※※" NOR + HIW "  脈  " NOR + RED "※※\n"
        "             ※※      ※※            ※※      ※※\n"
        "             ※※" NOR + HIW "  崩  " NOR + RED "※※            ※※" NOR + HIW "  呈  " NOR + RED "※※\n"
        "             ※※      ※※            ※※      ※※\n"
        "             ※※" NOR + HIW "  裂  " NOR + RED "※※            ※※" NOR + HIW "  現  " NOR + RED "※※\n"
        "             ※※      ※※            ※※      ※※\n"
        "             ※※" NOR + HIW "  時  " NOR + RED "※※            ※※" NOR + HIW "  間  " NOR + RED "※※\n"
        "             ※※    　※※            ※※      ※※\n"
        "             ※※※※※※※            ※※※※※※※\n"
        "             ※※※※※※※            ※※※※※※※\n" NOR;
}