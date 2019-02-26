// 揀竹籤遊戲，每次拿1-3根，拿到最後一根的輸

#define                MATCHNUM        15        
#define                MAXNUM                3
#define         obname  query("name", ob)
#define         REMAIN        query_temp("match_game/remain", me)

int play_game( object me, object ob )
{
        set_temp("match_game/turn", 1, me);
        set_temp("match_game/remain", MATCHNUM, me);
        set_temp("match_game/last", 0, me);
        set_temp("match_game/playing", 1, me);
        message_vision(obname+"不知從哪裏拿出幾根竹籤擺在桌子上。\n", me);
        command("say 這裏有"+chinese_number(MATCHNUM)+"根竹籤，每次最多拿三根，最少一根，不能不拿。誰拿到最後一根算輸。");
        command("say 你先拿吧。\n");
        add_action("take_match","take");
        write(YEL +"你可以用 take + 根數 來玩。\n\n"+ NOR);
        return 1;
}


int take_match(string arg)
{
        int n;
        object me = this_player();
        object ob = this_object();
        
        if( query_temp("match_game/win", me) || query_temp("match_game/lost", me) )
                return         notify_fail("遊戲已經結束了。\n\n");
        n = atoi(arg);
        if (!intp(n))
                return notify_fail("你要拿什麼？\n");
        if (n > MAXNUM || n <= 0)
                return notify_fail("一次只能拿一到"+chinese_number(MAXNUM)+"根竹籤。\n");
        if (n > REMAIN) 
                return notify_fail("只剩下"+chinese_number(REMAIN)+"根竹籤了。\n");
        addn_temp("match_game/remain", -n, me);
        message_vision("$N拿了"+chinese_number(n)+"根竹籤\n", me);
        if (REMAIN == 0) {
                message_vision(WHT +"沒有竹籤了，$N輸了。\n"+ NOR, me);
                message_vision(obname+"笑着拍着手，對$N叫到：你好笨喔，你輸啦！\n\n", me);
                set_temp("match_game/lost", 1, me);
                delete_temp("match_game/playing", me);
                return 1;                
        }
        else {
                message_vision("還剩下"+chinese_number(REMAIN)+"根竹籤。\n\n", me);
                for (n = REMAIN; n > MAXNUM; n = n - MAXNUM - 1);
                n = (n + 3) % 4;
                if (n == 0)
                           n = (REMAIN > MAXNUM ? random(MAXNUM)+1 : random(REMAIN)+1); 
                addn_temp("match_game/remain", -n, me);
                message_vision(obname+"拿了"+chinese_number(n)+"根竹籤。\n", me);
                if (REMAIN != 0) {
                        if (REMAIN == 1) {
                                set_temp("match_game/lost", 1, me);
                                delete_temp("match_game/playing", me);
                                message_vision(WHT +"還剩下"+chinese_number(REMAIN)+"根竹籤，$N輸了。\n"+ NOR, me);
                                message_vision(obname+"笑着拍着手，對$N叫到：你好笨喔，你輸啦！\n\n", me);
                                return 1;
                        }
                        else                                
                                message_vision("還剩下"+chinese_number(REMAIN)+"根竹籤，該$N拿了。\n\n", me);
                }
                else {
                        message_vision(HIW +"沒有竹籤了，$N贏了。\n"+ NOR, me);
                        message_vision(obname+"看了看手裏的竹籤又看了看$N，説道：是你瞎貓碰着死耗子，便宜你了。\n\n", me);
                        set_temp("match_game/win", 1, me);
                        delete_temp("match_game/playing", me);
                        return 1;
                }
        }
        return 1;
}
