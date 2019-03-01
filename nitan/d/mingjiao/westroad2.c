//westroad2.c

inherit ROOM;

void create()
{
        set("short", "深山");
        set("long", @LONG
已經走了很久，山林越來越密，夜晚來臨了，夜梟呼號，令人毛
骨悚然。真是『蜀道難，難于上青天』。再向西，就要出山了。突然，
你又發現南面有零星火光。
LONG );
        set("outdoors", "mingjiao");
        set("exits",([
            "east" : __DIR__"westroad1",
            "west" : __DIR__"gebitan1",
            "south" : __DIR__"miaorenbuluo",
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}