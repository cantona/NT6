// Room: /d/jiaxing/Yanyu2.c  煙雨樓二樓
// Last Modified by winder on Nov. 17 2000

#include <ansi.h>

inherit ROOM;

string look_bian();
int do_halloa(string arg);

void create()
{
        set("short", "煙雨樓二樓");
        set("long", @LONG
煙雨樓在南湖畔，四望臨風，醺醺醉人。柳岸翻曳，禽噪起伏。湖
面輕煙薄霧，幾尾小舟盪漾其間。半湖水裡都浮著碧油油的菱葉，越女
輕歌，嬌痴無那。你放眼觀賞，美景無限，胸懷大暢之下只想大聲喊叫
(halloa)。

    樓中立了一幅長匾(bian)，絞絲鑲邊，楠木為裡，年代雖久，桐油
粉漆，猶自清新如昨。柱子上隱隱有些字跡（ziji）。
LONG );
        set("no_sleep_room",1);
        set("item_desc", ([
            "ziji" : "江南七怪叫板邱處機處。\n",
            "bian" : (: look_bian :),
        ]));

        set("exits", ([
            "down"     : __DIR__"yanyu",
        ]));
        set("no_clean_up", 0);
	set("coor/x", 1210);
	set("coor/y", -1790);
	set("coor/z", 10);
	setup();
}

void init()
{
        object me = this_player();
        mapping myfam;
        
        add_action("do_halloa", "halloa");
        myfam=query("family", me);
        if (!mapp(myfam) || !stringp(myfam["family_name"])) return 0;
        
        if (myfam["family_name"] == "白駝山派" && me->query_condition("ice_sting")
                && me->query_condition("ice_sting") < 10) {
                message_vision(HIB"$N只覺得左臂越來越是腫大，情狀兇險無比，再不救治就來不及了！\n", me);
                message_vision(HIG"忽聽得背後一人說道：”小娃娃，知道厲害了吧！“，聲音鏗鏘刺耳，\n", me);
                message_vision("$N吃了一驚，急忙轉過身來，只見一個怪人，雙手各持一塊石頭，以手為足，\n", me);
                message_vision("”砵，砵，砵“地走了過來，那人怪眼一翻：”小娃兒，要命的跟我來。“ \n", me);
                message_vision("說罷，雙手一發勁，越上了屋頂。$N知道遇上了救星，大喜過望，連忙攀爬而上。\n"NOR, me);
                me->move(__DIR__"yanyu3");
        }
}

int do_halloa(string arg)
{
        object me = this_player();
        mapping myfam;
        
        if (!arg || arg != "義父") return 0;
        
        myfam=query("family", me);
        
        if (!mapp(myfam) || !stringp(myfam["family_name"])) return 0;
        if (myfam["family_name"] == "白駝山派" && myfam["master_id"] == "ouyang feng") {
                message_vision(HIC"$N氣沉丹田，長嘯一聲：“義父，你在哪裡？”\n", me);
                message_vision("過了半晌，耳畔傳來熟悉的“砵，砵，砵”的聲響，歐陽鋒從樓頂一躍而下。\n", me);
                message_vision("歐陽鋒對著$N點了點頭：”乖孩子，你又來學功夫了，跟我來吧！\n"NOR, me);
                me->move(__DIR__"yanyu3");
                return 1;
        } else  return notify_fail("叫蝦米叫，你義父是誰？\n");
}

string look_bian()
{
        return
        "※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※\n"
        "※※※※　　　                    　　　　　　　　　　　　※※※※\n"
        "※※※※　　　　            　西洲曲    　        　　　　※※※※\n"
        "※※※※　                                            　　※※※※\n"
        "※※※※　憶梅下西洲  折梅寄江北  單衫杏子紅  雙鬢鴉雛色　※※※※\n"
        "※※※※　西洲在何處  雙槳搖頭度  日暮伯勞飛  風吹烏□樹　※※※※\n"
        "※※※※　樹下即門前  門中露翠鈿  開門郎不至  出門採紅蓮　※※※※\n"
        "※※※※　採蓮南塘秋  蓮花過人頭  低頭弄蓮子  蓮子清如水　※※※※\n"
        "※※※※　置蓮懷袖中  蓮心徹底紅  憶郎郎不至  仰首思飛鴻　※※※※\n"
        "※※※※　飛鴻滿西洲  望樓上青樓  樓高望不見  盡日欄桿頭　※※※※\n"
        "※※※※　欄桿十二曲  垂手明如玉  卷簾天自高  海水搖空綠　※※※※\n"
        "※※※※　海水夢悠悠  君愁我亦愁  南風如我意  吹夢到西洲　※※※※\n"
        "※※※※　　　　　　　　　　　                    　　　　※※※※\n"
        "※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※※\n";
}