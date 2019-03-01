//Room: /d/dali/heshang.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","河上");
        set("long",@LONG
你正身處波濤滾滾的瀘水之上百多尺的空中。這是一座烏夷族特
有之藤橋，三根粗大的藤條呈一個倒“品”字形，腳踩下面一條，手
扶左右兩條，攀援而過看來驚險，實際上倒也不十分困難。一陣山風
挾着腳下激流飛濺的水花吹過，你感到一陣寒意。
LONG);
        set("outdoors", "daliw");
        set("exits",([ /* sizeof() == 1 */
            "east"      : __DIR__"cangshanlu1",
            "west"      : __DIR__"hebian",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19200);
	set("coor/y", -6830);
	set("coor/z", 20);
	setup();
}
int valid_leave(object me, string dir)
{
        int c_exp,c_skill;
        if (me->query_dex()<25)
        {
                tell_object(me,"你往藤橋下看了一眼，忽然怕了。\n");
                me->unconcious();
        }
        return 1;
}