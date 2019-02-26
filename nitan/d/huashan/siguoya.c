// siguoya.c
// Dec.11 1997 by Venus
inherit ROOM;
void create()
{
        set("short", "思過崖");
        set("long", @LONG
這是華山的思過崖。危崖上有個山洞，是華山派歷代弟子犯規後
囚禁受罰之所。崖上光禿禿的寸草不生，更無一株樹木。這危崖自來
自來相傳是玉女髮釵上的一顆珍珠，當年華山派的祖師以此危崖為懲
罰弟子之所，主要是此處無草無木，無蟲無鳥，受罰的弟子在面壁思
過之時，不致為外物所擾，心有旁鶩。
LONG );
        set("exits", ([ /* sizeof() == 2 */
                "northdown" : __DIR__"yunupath2",
                "enter"     : __DIR__"sgyhole1",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "huashan" );
        setup();
}
 
void init()
{
        object me = this_player();
        
        if( query_temp("xunshan", me) )
                set_temp("xunshan/siguo", 1, me);
                
        add_action("do_say", "say");
        
        return;
}


void do_say(string arg)
{  
        string name;
        object me = this_player();
        
        if (! arg || arg == "") return;
        
        if( arg == "風清揚" && !query_temp("marks/風", me) && random(30) == 5 )
        {
                message_vision("突然$N背後傳來一聲長歎：“難得這世上居然還有人知道風某的名字。”\n", me);
                message_vision("$N回過頭來，見山洞口站着一個白鬚青袍老者，神氣抑鬱，臉如金紙。\n", me);
                set_temp("marks/風", 1, me);
                if( query("shen", me) >= 10000 )
                {      
                        message("vision","風清揚對" + me->name() + "低聲地説了幾句話。説罷便飄然下山。\n", 
                                environment(me), ({me}));         
                        write( "風清揚低聲地説道：“當年獨孤求敗前輩以一柄玄鐵重劍稱雄江湖，\n");
                        write( "號稱「劍魔」，走遍天下欲覓一對手而不獲，為求一敗而不得，一生\n");
                        write( "寂寂。最終與一神鵰歸隱，埋劍「劍冢」。嗚呼！羣雄束手，長劍空\n");
                        write( "利，不亦悲夫！據聞「劍冢」的所在地是位於襄陽城外附近，心存誠\n");
                        write( "意，入口自現。至於到底如何心存誠意，則非我所知。希望你能尋得\n");
                        write( "寶劍，造福武林。\n");
                        write( "風清揚説罷，便飄然下山。\n");
                }
                else 
                {        
                          message_vision( "風清揚説罷，又對$N一聲長歎，便飄然下山離去。\n", me );
                }        
        }
        
        if( arg == "風清揚" && query_temp("marks/風", me) )
        {
                write( "清楓突然跳了出來説道：“不是見過風清揚了嗎？還不快去找玄鐵劍？”\n");
        }  
        
        return;
}                 