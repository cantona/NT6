// Room: /d/yanping/banyanting.c
// Date: Sep 28, 2002  Winder

#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", "半巖亭");
        set("long", @LONG
三千八百坎古趣盎然，山徑林蔭蔽日，盛夏無暑，蟬鳴鳥語，深曠
幽靜。循蜿蜒曲折的石階而行，途經三個涼亭，以半巖亭最為形勝。半
巖亭往上，地勢危岌，左是深壑，右是峭巖，春夏之時瀑布從巖頂飛瀉
而下，煞為壯觀。延平八景之一的“中巖飛瀑”(pu)即是指此。
LONG );
        set("exits", ([
                "northup"   : __DIR__"gubao",
                "southdown" : __DIR__"3800kan",
        ]));
        set("item_desc", ([
                "pu" : 
HIC"        中巖瀑布\n"HIY"                    劉璋(明)"NOR"
飛流一萬丈， 界破碧山煙。
醉眼朦朧看， 長虹飲玉川。\n"HIY"
                    廖紀(明)"NOR"
山中有靜者， 木食衣草萊。
白杼三千尺， 朝朝浣劫灰。\n"HIY"
                    吳恭(明)"NOR"
銀河垂地三千尺， 掛在中巖石壁端。
瀑布倒懸秋色凈， 雪花飛墜曉光寒。
谷深信有神龍蟄， 歲旱寧憂海水乾。
更欲攜琴來此處， 擬邀莊子共盤桓。
\n",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "yanping");
        set("coor/x", 1500);
        set("coor/y", -6120);
        set("coor/z", 30);
        setup();
        replace_program(ROOM);
}