// /d/shenlong/snakeroom.h
// Last Modified by winder on Jul. 12 2002

#include <ansi.h>

void init()
{
        object me = this_player();

        if( interactive(me) &&
                !objectp(present("xiong huang", me)) &&
                !objectp(present("snake", this_object())) &&
                random(query("combat_exp", me))<25000 )
        {
                remove_call_out("showup"); 
                call_out("showup", 1 + random(3));
        }
}

void showup()
{
        string snakefile, *snakegroup;
        object snake;

        snakegroup = query("snaketype");
        snakefile = snakegroup[random(sizeof(snakegroup))];
        snakefile = "/d/shenlong/npc/" + snakefile;

        snake = new(snakefile);

        message("vision",HIR"突然一條"+query("name", snake)+"從不知什麼地方遊了出來！！！\n"NOR,this_object());
        snake->move(this_object());

        remove_call_out("disappear");
        call_out("disappear", 10 + random(10), snake);
}

void disappear(object snake)
{
        if( !objectp(snake) ) 
                return;

        if( !living(snake) || snake->is_fighting() || snake->is_busy() )
        {
                call_out("disappear", 10 + random(10), snake);
                return;
        }

        message_vision("只見$N飛快地遊走了。\n", snake);
        destruct(snake);
}
