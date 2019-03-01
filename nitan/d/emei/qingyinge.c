#include <ansi.h>
inherit ROOM;

string look_shibei();

void create()
{
      set("short","清音閣");
        set("long", @LONG
這裡是峨嵋山的清音閣。此閣位于牛心嶺下，東有白龍江西有黑
龍江，兩江之水交匯于清音閣下。江上有拱橋兩座，分夸黑龍白龍二
江，這就是雙飛橋。兩江合流處，有一數米高的黑褐色巨石傲然挺立，
形似牛心，名之為「牛心石」。橋邊立有一石碑(shibei)。由此向西
上，左行是黑龍江棧道，右路至白龍洞，東去中峰寺。
LONG );
      set("outdoors", "emei");
      set("objects", ([
           CLASS_D("emei") + "/xian" : 1,
           __DIR__"npc/girldizi" : 1,
      ]));

      set("item_desc", ([
          "shibei" : (: look_shibei :),
      ]));

      set("exits", ([
          "west"  : __DIR__"bailongdong",
          "east"  : __DIR__"zhongfengsi",
          "south" : __DIR__"heilong1",
      ]));
        set("coor/x", -460);
        set("coor/y", -230);
        set("coor/z", 80);
        setup();
}

string look_shibei()
{
        return

WHT "\n石碑刻有一詩曰：\n\n"
"          ※※※※※※※※※※※※※※\n"
"          ※                        ※\n"
"　　　　　※　" HIC "傑 然 高 閣 出 清 音" NOR + WHT "  ※\n"
"          ※                        ※\n"
"　　　　　※　" HIC "仿 佛 仙 人 下 撫 琴" NOR + WHT "  ※\n"
"          ※                        ※\n"
"　　　　　※　" HIC "試 向 雙 溪 一 傾 耳" NOR + WHT "  ※\n"
"          ※                        ※\n"
"　　　　　※　" HIC "無 情 兩 水 漱 牛 心" NOR + WHT "  ※\n"
"          ※                        ※\n"
"          ※※※※※※※※※※※※※※\n\n"
"這就是「峨嵋十景詩」中專詠這「雙橋清音」的詩。\n" NOR;
}