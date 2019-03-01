// Room: /binghuo/wangpangu2.c
// Date: Oct.28 1999 by Winder

inherit ROOM;

void create()
{
/*
        set("short", "山谷");
        set("long", @LONG
四周長滿了幾百株合抱大鬆樹。左首山峰前一堵大石壁，壁上刻
著廿四字(zi)，縱橫開闔，宛如施展拳腳一般。但見筆劃多的不覺其
繁，筆劃少的不見其陋，其縮也凝重，似尺蠖之屈，其縱也險勁，如
狡兔之脫，淋漓酣暢，雄渾剛健，俊逸處如風飄，如雪舞，厚重處如
虎蹲，如象步。其中兩個“不”字，兩個“天”字，但兩字寫來形同
而意不同，氣似而神不似，變化之妙，又是另具一功。尤其是“鋒”
字最後一筆，直劃下來，當真是星劍光芒，如矢應機，霆不暇發，電
不及飛。
LONG );
*/
        set("short", "揚刀立威會場");
        set("long", @LONG
這裡是揚刀立威會場，一片青草地上擺著七八張方桌，除了東首第一席外，
每張桌旁都已坐了人，有海沙派、巨鯨幫、神拳門等等各派弟子。
LONG );
        set("no_sleep_room",1);
        set("outdoors", "wangpan");
        set("item_desc", ([
                "zi": 
"　　　　※※※※※※※※※※※※※※※※※※※※※※※\n"
"　　　　※※※※　　        　　　　　　　　　※※※※\n"
"　　　　※※※※　　誰　倚　莫　號　寶　武　　※※※※\n"
"　　　　※※※※　　        　　　　　　　　　※※※※\n"
"　　　　※※※※　　與　天　敢　令　刀　林    ※※※※\n"
"　　　　※※※※　　        　　　　　　　　　※※※※\n"
"　　　　※※※※　　爭　不　不　天　屠　至　　※※※※\n"
"　　　　※※※※　　        　　　　　　　　　※※※※\n"
"　　　　※※※※　　鋒　出　從　下　龍　尊　　※※※※\n"
"　　　　※※※※　　　　　　                　※※※※\n"
"　　　　※※※※※※※※※※※※※※※※※※※※※※※\n",
        ]));
        set("exits", ([
                "north"     : __DIR__"wangpangu1",
                "northeast" : __DIR__"wangpanlin",
        ]));
        set("objects", ([
                "/d/tulong/tulong/npc/mai" : 1,
                "/d/tulong/tulong/npc/guo" : 1,
                "/d/tulong/tulong/npc/yin" : 1,
                "/d/tulong/tulong/npc/yuan" : 1,
                "/d/tulong/tulong/obj/ding" : 1,
                "/d/tulong/tulong/npc/zhang" : 1,
                "/d/tulong/tulong/npc/chang" : 1,
        ]));
        setup();
}

void reset()
{

        object item, con;
        ::reset();
        con = present( "ding", this_object());
        item = find_object("/d/tulong/obj/tulongdao");
        if( !objectp(item) || !environment(item) ) {
                item = get_object("/d/tulong/obj/tulongdao");
                item->move(con);
                item->start_borrowing();
        }
}

