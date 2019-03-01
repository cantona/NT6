// Room: /d/gaibang/undertre.c
// Date: Haa 96/03/22

inherit ROOM;

void create()
{
        set("short", "樹洞下");
        set("long", @LONG
這是老槐樹底部，四周光線昏暗，人影晃晃，似乎有幾個黑暗的洞
口在你身邊，通向四面八方。一位老乞丐大咧咧地坐在正中的地上。不
經意中你發現牆壁上畫著幅粗糙的路線草圖（map）。
LONG );
        set("no_fight", 1);
        set("exits", ([
                "up"   : __DIR__"inhole",
                "west" : __DIR__"chuchang",
                "0"    : __DIR__"yyandao1",
                "1"    : __DIR__"xcandao1",
                "2"    : __DIR__"zlandao1",
                "3"    : __DIR__"slandao1",
                "4"    : __DIR__"xxandao1",
                "5"    : __DIR__"wdandao1",
                "6"    : __DIR__"hsandao1",
                "7"    : __DIR__"bjandao1",
                "8"    : __DIR__"qzandao1",
                "9"    : __DIR__"xsandao1",
                "a"    : __DIR__"dlandao1",
                "b"    : __DIR__"fzandao1",
                "c"    : __DIR__"wxandao1",
                "f"    : __DIR__"cdandao1",
        ]));
        set("item_desc",([ "map" :
                "出口零：通往岳陽。\n"
                "出口一：通往小村。\n" +
                "出口二：通往竹林。\n" +
                "出口三：通往少林。\n" +
                "出口四：通往星宿。\n" +
                "出口五：通往武當。\n" +
                "出口六: 通往華山。\n" +
                "出口七：通往北京。\n" +
                "出口八：通往嘉興。\n" +
                "出口九：通往雪山。\n" +
                "出口Ａ：通往大理。\n" +
                "出口Ｂ：通往福州。\n"
                "出口Ｃ：通往無錫。\n"
                "出口Ｆ：通往成都。\n"
        ]));
        set("objects",([
                CLASS_D("gaibang") + "/liang" : 1,
                "/d/gaibang/npc/5dai" : 1,
                "/d/gaibang/npc/6dai" : 1,
                "/d/gaibang/npc/7dai" : 1,
        ]));
        set("coor/x", 10);
        set("coor/y", -10);
        set("coor/z", -20);
        setup();
        "/clone/board/gaibang_r"->foo();
}

void init()
{
        object ob = this_player();
        mapping myfam;
        myfam=query("family", ob);
        if (!myfam || myfam["family_name"] != "丐幫")
        {
                message_vision("\n粱長老看到$N闖進來，大喝一聲：你不是丐幫弟子，給我滾出去！\n\n", ob);
                ob->move("/d/gaibang/inhole");
                message("vision","只聽“乒”地一聲，"+query("name", ob)+"從小門裡飛了出來。\n",environment(ob),ob);
        }
}
int valid_leave(object me, string dir)
{
        object guarder;

        if (objectp(guarder = present("liang zhanglao", this_object())) &&
            living(guarder) && dir != "up")
                return guarder->permit_pass(me, dir);

        return ::valid_leave(me, dir);
}