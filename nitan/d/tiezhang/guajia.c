#include <ansi.h>
#include <room.h>

inherit ROOM;

void create()
{
        set("short", GRN "瓜架" NOR);
        set("long", @LONG
轉過一個小彎，忽然眼前一綠，面前是一片很大的瓜架。在高大的木架
旁，種植著一些蔬菜和瓜類，架子上已經爬滿了各種各樣的植物，從茂密的
葉子中，垂下各種已經成熟的果實，絲瓜，苦瓜，葫蘆……還有一些叫不出
名稱的瓜果也纏雜在其中。
LONG    );
        set("exits", ([
                "southeast" : __DIR__"shuijing",
                "west" : __DIR__"guangchang",
        ]));

        set("objects", ([
                CLASS_D("tiezhang") + "/qiuqianzhang" : 1,
        ]));

        set("no_clean_up", 0);
        set("hulu_count", 5);
        set("outdoors", "tiezhang");

        setup();
}