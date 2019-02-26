// Room: /d/yueyang/fengshanyin.c
// Last Modifyed by Winder on Dec. 4 2001

inherit ROOM;

void create()
{
        set("short", "封山印");
        set("long", @LONG
在龍口東側、二妃墓西側的臨湖岸邊上，原有四顆秦始皇的封山印
(yin) ，如今僅存其二。相傳秦始皇六合一統後南巡瀟湘，在洞庭湖留
印封山，欲伏風浪。如今碧山仍在，綠樹長青，君臨天下的始皇帝呢，
唯留荒冢。史浪蕩滌，滄海桑田，慷慨如是。
LONG );
        set("outdoors", "dongting");
        set("no_clean_up", 0);
        set("item_desc", ([
                "yin" : "
    始皇帝南巡乘船至此附近突然湖風濁浪，船不能行進，便問左右：
“此乃何地？”侍臣回報：“此地名君山，湘君女神之的所在，故作此
患。”始皇帝聽後大怒曰：“豈有君之理？”侍臣勸其上山拜求湘君，
求湘水神寧波息浪，始皇帝恃其萬乘之威，不肯求拜，反令刑徒三千伐
盡其樹，放火燒山毀盡其廟宇、亭台，並以九龍鑲金的玉璽，對準巖石
用力蓋去，留印封山，意欲使湘水女神不再為患。不意洞庭湖仍湖風大
作，波浪滔天，船隻被阻隔在君山。始皇帝始知無奈湘水神何，終致登
山求拜，風浪而後息，船隻始得暢通。\n"
        ]));
        set("exits", ([
                "northwest" : __DIR__"xiaolu1",
                "northeast" : __DIR__"xiaolu3",
        ]));
        set("coor/x", -1700);
        set("coor/y", 2270);
        set("coor/z", -20);
        setup();
        replace_program(ROOM);
}