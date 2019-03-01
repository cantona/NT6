#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "匯英酒樓");
        set("long", @LONG
匯英酒樓裡桌椅潔凈，座中客人衣飾豪奢，十九都是富商
大賈。這裡可以俯瞰整個紫禁城的全景。
LONG);
        set("exits", ([
                "down" : "/d/beijing/huiying",
        ]));

        if (random(5) > 2)
        {
                set("story", 1);
                set("objects", ([
                        CLASS_D("gaibang") + "/ada" : 1,
                        __DIR__"npc/zhaomin2" : 1,
                        __DIR__"npc/zhao1" : 1,
                        __DIR__"npc/qian2" : 1,
                ]));
        }
        setup();
}

void init()
{
        if (query("story"))
        {
                remove_call_out("check");
                call_out("check", 800);
        }
}

void check()
{
        object ob = this_object();
        object npc1, npc2, npc3, npc4;

        npc1 = present("zhao min", ob);
        npc2 = present("a da", ob);
        npc3 = present("zhao yishang", ob);
        npc4 = present("qian erbai", ob);

        if (! npc1 || ! npc2)
                return 0;

        message_vision(CYN "$N" CYN "打了個哈欠，說道：時間不"
                       "早了，我們回去吧。\n$n" CYN "點了點頭"
                       "道：甚好，我們這就走吧。\n\n" HIY "說"
                       "罷便見幾人一齊站起，護著$N" HIY "離開"
                       "了酒樓。\n\n" NOR, npc1, npc2);

        if (objectp(npc1))
                destruct(npc1);

        if (objectp(npc2))
                destruct(npc2);

        if (objectp(npc3))
                destruct(npc3);

        if (objectp(npc4))
                destruct(npc4);
}