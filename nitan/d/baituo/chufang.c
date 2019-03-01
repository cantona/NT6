//chufang.c

inherit ROOM;
void create()
{
        set("short","廚房");
        set("long", @LONG
這是間寬敞的廚房，廚師們在展示各自的烹飪絕活。整個房間彌
漫著令人垂涎欲滴的菜香。牆上貼著一張醒目的啟事(note)。
LONG );

        set("exits",([
                "west" : __DIR__"huayuan",
                "east" : __DIR__"chaifang",
        ]));

        set("item_desc",([
                "note" : "本廚房招收小工：每砍一擔柴，付１０兩銀子。\n",
        ]));

        set("objects",([
                __DIR__"npc/feifei"   : 1,
                __DIR__"obj/doujiang" : 5 + random(3),
                __DIR__"obj/cake"     : 5 + random(3),
        ]));

        set("resource/water", 1);
        set("no_beg", "1");

        set("coor/x", -49980);
        set("coor/y", 20050);
        set("coor/z", 30);
        setup();
}

int valid_leave(object me, string dir)
{
        if (( present("jiang", me)||present("cake", me))
        && objectp(present("fei fei", environment(me))) )
                return notify_fail("肥肥一把拽住你的衣領，"
                                   "著急地叫到：飯菜不能帶出去，"
                                   "這裡蟑螂已經夠多了。\n");
        return ::valid_leave(me, dir);
}
