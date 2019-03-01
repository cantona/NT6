// Room: /binghuo/wangpangang.c
// Date: Oct.28 1999 by Winder
#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", "王盤山漁港");
        set("long", @LONG
這裡就是王盤島山漁港了。北邊是一望無際的大海；往西北是一
片樹林。島上的空氣似乎又熱又悶，咸濕的海風中帶著一股腥臭。海
邊泊著幾艘大船(chuan)。
LONG );
        set("outdoors", "wangpan");
        set("no_clean_up", 0);
        set("item_desc", ([
                "chuan" : "幾艘遠洋大海船。上船(enter)就可以出海。\n",
        ]));
        set("exits", ([
                "northwest" : __DIR__"wangpanlin",
        ]));
        setup();
}

void init()
{
        add_action("do_enter", "enter");
}
int do_enter ( string arg )
{
        object ob ;
        string dir;
        if( !arg || arg !="chuan" ) 
        {
                tell_object(this_player() , "你要 enter 哪兒？\n" ) ;
                return 1 ;
        }
        ob = this_player ();
        if (random(4) > 1)
        {
                message_vision("風帆升起，船頭緩緩轉過，風向逆轉，船反而向西方航行。\n", ob);
                ob ->move(__DIR__"westboat") ;
                tell_object(ob, BLU "你在錢塘江上順風順水兜風，心情蠻好.......\n" NOR ) ;
                call_out("home", 10 , ob );
        }
        else
        {
                message_vision("風帆升起，船頭緩緩轉過，風力漸勁，船向東方大海深處航行。\n", ob);
                ob ->move(__DIR__"eastboat1") ;
                tell_object(ob, BLU "你在海上憑欄戲鷗，心情起伏不寧......\n" NOR ) ;
                call_out("fore1", 10 , ob );
        }
        return 1 ;
}
void home( object ob )
{
        tell_object(ob , "船很快就回到杭州了。你走下船來。\n" ) ;
        ob->move (__DIR__"qiantang") ;
}
void fore1( object ob )
{
        tell_object(ob , "四周一望無際的大海。你不禁有點心下惴惴。\n" ) ;
        ob->move (__DIR__"eastboat2") ;
        tell_object(ob, BLU "這船去哪裡呢？你不禁有點緊張......\n" NOR ) ;
        call_out("fore2", 10 , ob );
}
void fore2( object ob )
{
        tell_object(ob , "船很快就靠上島了。你走下船來。\n" ) ;
        ob->move (__DIR__"lingshedao") ;
}