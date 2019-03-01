// Room: /d/shaolin/guangchang1w.c
// Date: CSWORD 96/02/28

inherit ROOM;

void create()
{
        set("short", "廣場");
        set("long", @LONG
這裏是少林寺前的廣場，整個廣場由大塊的青石鋪成，極為平坦。
但因年代久遠，都有些破損。叢叢小草從石板的縫隙中長了出來。廣
場周圍都是密密的松樹林，四角上各放了幾塊石碑，字跡都甚為模糊。
邊上立了塊木牌(mupai)，寺前三三兩兩的站着幾個僧人。
LONG );
        set("exits", ([
                "west" : __DIR__"shulin1",
                "southdown" : __DIR__"shijie11",
                "east" : __DIR__"guangchang1",
        ]));
        set("item_desc",([
                "mupai"        :   "少林寺護法松林，違令擅入者殺無赦！\n",
        ]));
//        set("no_clean_up", 0);
        set("outdoors", "shaolin");
        set("objects",([
                CLASS_D("shaolin") + "/qing-wei" : 1,
        ]));
        setup();
}

int valid_leave(object me, string dir)
{
        if (!wizardp(me) 
        && dir == "west" 
        && me->query_skill("dodge",1) <= 20 
        && (present("qingwei biqiu", environment(me))))

        return notify_fail("清為攔住勸你: 西邊是本寺護法松林，向來有進無出，\n"
                    + RANK_D->query_respect(me) + "輕功不佳，最好先看看木牌，不要隨便進去！\n");

        return ::valid_leave(me, dir);
}
