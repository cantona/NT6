inherit ROOM;

void create()
{
        set("short","水蓮洞內");
        set("long", @LONG
這裏一片漆黑，什麼都看不見，只聽見水滴的聲音。
LONG );
        set("exits",([
               "east" :__DIR__"inhole2",           
        ]));
        
        set("objects",([
               "/clone/beast/yanjingshe" : 1,
        ]));
        
        setup();

}

void init()
{
               object me = this_player();

               if (present("fire", me))
               {
                       set("long", @LONG
越往裏面走道路越是狹窄，洞裏也是一絲陽光也射不進來，
如果沒有火折的話，恐怕是寸步難行。不知道這條路是通向什
麼地方，你只覺得這裏陰風瑟瑟，不由地打了個寒顫。
LONG);
                       set("exits/west",__DIR__"zigai4",);
               }
               return ;
}