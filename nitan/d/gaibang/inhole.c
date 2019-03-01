// Room: /d/gaibang/inhole.c
// Date: Haa 96/03/22

inherit ROOM;
int do_say(string arg);
void create()
{
        set("short", "樹洞內部");
        set("long", @LONG
這是楊州城中央廣場的老槐樹內部，也是丐幫秘密的地下通道的總交
匯處。樹洞裡丟滿了各種拉圾，弭漫著一股臭哄哄的味道。樹洞壁上釘著
一塊非常醒目的木牌（board）。
LONG );
        set("exits", ([
           "out" : "/d/city/guangchang"
        ]));
        set("item_desc",([
                "board"        : "富人地獄，窮人天堂。\n"
        ]));
        set("objects",([
                "/d/gaibang/npc/2dai" : 1 + random(2),
                "/d/gaibang/npc/1dai" : 1 + random(2),
                CLASS_D("gaibang") + "/zuo-qu" : 1,
        ]));
        set("no_clean_up", 0);
        set("coor/x", 10);
        set("coor/y", -10);
        set("coor/z", -10);
        setup();
}

void init()
{
        add_action("do_say", "say");
}

int do_say(string arg)
{
        if( arg=="天堂有路你不走呀" ||  arg=="地獄無門你進來啊")
        {
                write("只聽裡面有人說了聲：是本幫兄弟吧？請進來吧。\n");
                message("vision", "樹洞邊上一堵牆緩緩移了開來，原來是道小木門。\n", this_player());
                set("exits/down", __DIR__"undertre");
                remove_call_out("close");
                call_out("close", 5, this_object());
                return 1;
        }
        return 0;
}
void close(object room)
{
        message("vision","只見小木門乒地關上了。\n", room);
        delete("exits/down", room);
}