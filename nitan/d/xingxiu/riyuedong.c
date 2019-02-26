// Room: /d/xingxiu/riyuedong.c
// Last Modified by winder on Feb. 28 2001

inherit ROOM;

void create()
{
        set("short", "日月洞");
        set("long", @LONG
這裏是星宿派總舵所在地日月洞。洞內燈火通明，正中一把虎皮椅
上端坐着星宿派掌門人丁春秋。兩邊各站列着數十位星宿派弟子，不斷
有各派人士走進來獻(xian)上各種寶物。在一片歌功頌德之聲中，洋洋
盈耳，絲竹簫管也跟着吹奏。丁春秋每聽到得意之時，禁不住揮動手中
的羽扇，捋着白鬚，眯起了雙眼，薰薰然，飄飄然，有如飽醉醇酒。
    洞壁上裝飾着虎皮、鹿頭、雕羽，及一些字畫(zihua)。 洞兩側豎
立兵器架，上面排列的大多是各種棍棒。
LONG );
        set("exits", ([
                "south" : __DIR__"riyuedong1",
        ]));

        set("item_desc", ([
                "zihua" : "都是些吹捧星宿老仙的詩詞和他的畫像。\n

※※※※※※※※※※※※※※※※※
※※※※　　　　　　　　　※※※※
※※※※　古　威　德　星　※※※※
※※※※　今　震　配　宿　※※※※
※※※※　無　寰　天　老　※※※※
※※※※　比　宇　地　仙　※※※※
※※※※　　　　　　　　　※※※※
※※※※※※※※※※※※※※※※※
"
        ]) );

        set("objects", ([
                CLASS_D("xingxiu")+"/ding" : 1,
                __DIR__"npc/obj/tiegun" : 1,
                __DIR__"npc/obj/huoyan" : 1,
                "/clone/misc/muding" : 1,
        ]) );
//        set("no_clean_up", 0);
        set("coor/x", -50000);
        set("coor/y", 20400);
        set("coor/z", 100);
        setup();
        replace_program(ROOM);
}