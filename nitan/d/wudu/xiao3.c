#include <ansi.h>
inherit ROOM;

string look_pai();

void create()
{
        set("short", "江邊小路");
        set("long", @LONG
這裡是桃花江邊的一條泥土小路，一旁就是清澈的江水。夾岸連
綿不斷的桃花燦若雲霞，暗香襲人，引來許多蜜蜂在花樹間飛舞。前
面有一個木牌 (pai)立在路中央，由于風吹日曬，字跡已經模糊了。
LONG
        );
        set("outdoors", "wudujiao");

        set("exits", ([
                "southeast" : __DIR__"taohua",
                "northwest" : __DIR__"xiao2",
        ]));

        set("item_desc",([
                "pai" : (: look_pai :),

        ]));
   

        setup();
}

string look_pai()
{
    return
    "\n"
              WHT "          ################################\n"
                  "          ##                            ##\n"
                  "          ##          通     告         ##\n"
                  "          ##                            ##\n"
                  "          ##        前方乃桃花峪……    ##\n"
                  "          ##    內…瘴氣…危險。本村    ##\n"
                  "          ##    之人…嚴禁…闖入。      ##\n"
                  "          ##                            ##\n"
                  "          ##            村長  苗三斤    ##\n"
                  "          ##                            ##\n"
                  "          ################################\n\n" NOR;
    "\n";
}