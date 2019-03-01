#include <ansi.h>
inherit ROOM;
void create()
{
        set("short", "楓林渡");
        set("long",
"這裡是前往綠柳山莊的必經之路，一道小河橫在你的面前，上面結了\n"
"薄薄的一層冰。渡口旁邊一條破爛的布幅訂在樹上，白布在北風中飛舞，\n"
"你定睛一看，上面寫著幾個血字：\n"
HIR "                    一入此境，便無歸路\n" NOR
);

        set("exits", ([ /* sizeof() == 2 */
          "south" : __DIR__"inn",
          "north" : __DIR__"xueyuan",
        ]));    
        set("no_fight",1);                                 
       set ("no_look",1);
        setup();
}                                  

int init()
{
          add_action("do_north","gonorth");
}                

int valid_leave(object me,string dir)
{
        if( dir == "north" )
                return notify_fail(
                        "\n你要過去嗎？你真的要過去嗎？你該不是真想要過去吧。\n"        
                        "想要過去就說嘛。雖然你很有誠意的樣子徘徊在這裡，\n"
                        "可是你不說別人怎麼知道你要過去呢？你真的要過去嗎？\n"
                          "想要過去你就敲gonorth吧。\n\n"
                );
        return 1;
}

int do_north(string arg)
{
        object me;
        object *inv;
        int i;

        me = this_player();

        inv = all_inventory(me);
        for( i=0;i<sizeof(inv);i++) 
        {
                if( inv[i]->is_character() )
                {
                        write("你不能背著"+query("name", inv[i])+"進去!\n");
                        return 1;
                }
        }

        if( query("combat_exp", me)<2000000 )
        {       
                write(RED"前方路途險惡，還是不要去送死了吧。\n"NOR);
                return 1;
        }

        write(YEL"你鼓足勇氣，渡過河去，踏上了險惡的征程。\n"NOR);
        this_player()->move(__DIR__"xueyuan");

        return 1;
}
