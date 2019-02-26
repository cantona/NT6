//room: mumen.c

inherit ROOM;
void create()
{
        set("short","墓門");
        set("long", @LONG
這是個一座豪華墓地的墓門。大理石雕花的門樑，青石板的路面，
修剪整齊的長青木，顯得莊重肅穆。墓門邊立着一塊青白色石碑(bei
)。
LONG );
        set("exits",([
                "south" : __DIR__"fende",
        ]));
        set("item_desc",([
                "bei" : "   『公主墳』  \n無「金令牌」者禁入！\n",
        ]));
        set("objects",([
                __DIR__"npc/shiwei" : 1,
        ]));
        set("outdoors", "baituo");
 
        setup();
}

int valid_leave(object me, string dir)
{
       if (  (dir == "northeast")
           && (! present("jinpai", me))
           && objectp(present("shi wei", environment(me))) )
                return notify_fail
                        ("仕衞把手一攔：你沒有「金令牌」，不能進去！\n");
        return ::valid_leave(me, dir);
}
