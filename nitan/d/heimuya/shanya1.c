inherit ROOM;

void create()
{
        set("short", "成德殿大門");
        set("long", @LONG
此處入雲高聳，已是黑木崖上，兩旁站滿了日月神教的弟子。兩
旁的刻著兩行大字，右首是「文成武德」，左首是「仁義英明」，橫
額上刻著「日月光明」四個大紅字。
LONG );
        set("outdoors", "heimuya");
        set("exits", ([
                    "south" : __DIR__"shanya2",
                    "north" : __DIR__"chengdedian",
        ]));
        set("objects", ([
                __DIR__"npc/dizi" : 2,
                CLASS_D("riyue") + "/wang" : 1,
        ]));
        setup();
}

int valid_leave(object me, string dir)
{
        object wang;

        if (dir != "north"
           || ! objectp(wang = present("wang cheng", this_object())))
                return ::valid_leave(me, dir);

        return wang->permit_pass(me, dir);
}