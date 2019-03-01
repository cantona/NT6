// /guanwai/dongcheng.c

inherit ROOM;

void create()
{
        set("short", "東城");
        set("long", @LONG
這裏是用黃土鋪就的街道，街上的行人不多，看起來很冷清。偶爾有幾
個身着異域服飾的行人走過，看起來是滿族，鮮祖的居民。西面傳來嘈雜的
叫賣聲。南面是一排黃泥壘成的土房，裏面有嬉笑的聲音。
LONG );
        set("exits", ([
                "west"      : __DIR__"jishi",
                "south"     : __DIR__"tuyaoguan",
                "east"      : __DIR__"xuedi1",
                "northeast" : __DIR__"huandi1",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "guanwai");
        set("coor/x", 4000);
	set("coor/y", 9240);
	set("coor/z", 0);
	setup();
//        replace_program(ROOM);
}

int valid_leave(object me, string dir)
{
        if (dir == "east")
        {
                me->receive_damage("qi",30);
                me->receive_wound("qi",30);
        tell_object(me,"一股刺骨的寒風吹過，你只覺得渾身的血液都快被凍住了！\n");
        }
        return 1;
}