inherit ROOM;

void create()
{
        set("short", "青草坪");
        set("long", @LONG
這裡是樹林中的一片比較大的空地，名曰：青草坪。因為處于密
林之中所以這裡平時很少有人來，但是不知道為什麼今天這裡卻有不
少人。你看，又一個來了。
LONG );
        set("exits", ([
                "north" : __DIR__"xiaodao3",
                "south" : __DIR__"xiaodao5",
                "east"  : __DIR__"xiaodao4",
                "west"  : __DIR__"xiaodao1",
                "enter" : __DIR__"midao1",
        ]));
        set("outdoors", "xiaoyao");
        set("objects", ([
                CLASS_D("xiaoyao") + "/suxingh" : 1,
                CLASS_D("duan") + "/duanyq" : 1,
                CLASS_D("duan") + "/duanyu" : 1,
                __DIR__"npc/wangyuyan" : 1,
        ]));
        set("zhenlong", 1);
        set("valid_startroom", 1);
        setup();
        "/clone/board/xiaoyao_b"->foo();
}

int valid_leave(object me, string dir)
{
        object su;

        if (dir != "enter")
                return ::valid_leave(me, dir);

        if (! (su = present("su xinghe", this_object())) || ! living(su))
                return ::valid_leave(me, dir);

        if (! su->permit_pass(me, dir))
                return 0;

        return ::valid_leave(me, dir);
}

string long()
{
        string msg;
        int i;

        if (query("zhenlong"))
        {
                msg = "    空地中間擺了一副棋盤，上面放了不少的子。一"
                      "旁圍著不少的人在觀看，有的冥神思索，有的看似漫"
                      "不經心。";
        } else
                msg = "    ";
        if (present("duan yanqing", this_object()))
        {
                msg += "旁邊一怪客一襲青衫、容貌醜陋，冷酷異常，冷冷"
                       "的看著" + (query("zhenlong") ? "棋盤。" : "眾人。");
        }
        if (present("duan yu", this_object()))
        {
                if (present("wang yuyan", this_object()))
                        msg += "有一人最是奇特，長得風度翩翩，頗具"
                               "富貴氣相，卻總是瞅著身旁一女子，色迷"
                               "迷的樣子真是讓人心中竊笑。";
                else
                        msg += "有一人卻是失魂落魄，六神無主，仿佛"
                               "不見了什麼重要東西似的。";
        }

        return query("long") + sort_string(msg, 54);
}