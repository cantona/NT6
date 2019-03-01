// shidong.c
// Modified by Winder June.25 2000

inherit ROOM;
int do_push(string arg);

void create()
{
        set("short", "圓形石室");
        set("long", @LONG
這是座圓形石室，光亮從左邊透來，但朦朦朧朧地不似天光。細看
天光處，那是一扇窗，竟然是鑲在石壁的一塊大水晶，約有銅盆大小，
光亮便從水晶中透入。一尾大蝦在窗外遊過。接著一條花紋斑爛的鯉魚
在窗悠然而過。雙眼帖著水晶往外瞧去，只見碧綠水流不住幌動，魚蝦
水族來回遊動，極目所至，竟無盡處。原來處身之地竟在水底，當年造
石室之人花了偌大的心力，將外面的水光引了進來，這塊大水晶更是極
難得的寶物。室中放著一只石桌，桌前有凳，桌上堅著一銅鏡，鏡旁放
著些梳子釵釧之屬，看來竟是閨閣所居。銅鏡(mirror)上生滿銅綠，桌
上也是塵土寸積，不知已有多少年無人來此。
LONG );
        set("exits", ([
                "south" : __DIR__"damen",
                "east" : __DIR__"shiji2",
                "west" : __DIR__"shiji1",
        ]));
        set("item_desc", ([
                "mirror" : "忽見東首一面斜置的銅鏡反映光亮照向北隅，石壁\n上似有一道縫。\n",
        ]));
        set("coor/x", -50020);
        set("objects", ([
                CLASS_D("xiaoyao")+"/first" :1,
        ]));
        set("coor/y", -21040);
        set("coor/z", -40);
        setup();
}

void init()
{
        add_action("do_push", "push");
}

int do_push(string arg)
{
        object me;
        me = this_player();
        if (!arg||arg!="stone") return 0;
        write("你忙搶將過去，使力推那石壁。\n");
        if( random(query("kar", me))<10 || 
                me->query_skill("beiming-shengong",1) <= 40 )
        {
                write("那石壁推不動的。\n");
                return 1;
        };
        write("果然是一道門，緩緩移開，露出一洞來。\n");
        set("exits/north", "/d/xiaoyao/shishi3", this_object());
        return 1;
}
