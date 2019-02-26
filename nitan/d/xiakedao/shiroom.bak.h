int do_study(string arg)
{
        string *skill_name = ({
               "strike",          //趙客縵胡纓
               "sword",           //吳鈎霜雪明
               "dodge",           //銀鞍照白馬
               "throwing",        //颯沓如流星
               "pixie-jian",      //十步殺一人 sword
               "qiankundanuoyi",//千里不留行 dodge
               "lingboweibu",     //事了拂衣去 dodge
               "qimen-wuxing",   //深藏身與名 dodge
               "unarmed",         //閒過信陵飲 cuff or strike or unarmed
               "qimen-flee",      //脱劍膝前橫 sword
               "parry",           //將炙啖朱亥
               "blade",           //持觴勸侯嬴
               "axe",              //三杯吐然諾 force 暫時先count吧
               "whip",            //五獄倒為輕 cuff or strike or unarmed
               "staff",           //眼花耳熱後   魯達禪杖
               "taoism",          //競氣素霓生 cuff or strike or unarmed
               "hammer",          //救趙揮金錘 sword
               "buddhism",        //邯鄲先震驚 force
               "hubo",            //千秋二壯士
               "xiaowuxiang",           //亙赫大梁城 force
               "checking",        //縱死俠骨香   指法
               "club",            //不慚世上英   齊眉棍
               "kuihua-xinfa",    //誰能書閣下
               "taixuan-gong"     //白首太玄經
        });
        object me, where;
        int jing_cost, learn_pot, item, times, i, success=0;
        string skillname;
        int t;

        me = this_player();
        if( !arg ) return notify_fail("你要領悟什麼呀？\n");
        if( sscanf(arg, "%s %d", arg, times)!=2)
                return notify_fail("指令格式：think wall <次數>\n");
        if( ( arg != "wall" ) )
                return notify_fail("指令格式：think wall <次數>\n");
        t = 200;
        if( present("study emblem", me) )
                t += 1000;
        if( times < 1 || times > t )
                return notify_fail("領悟次數最少是一次，最多是" + CHINESE_D->chinese_number(t) + "次。\n");
        if( query("combat_exp", me)<500000 )
                return notify_fail("你的經驗太低, 沒法領悟石壁內容。\n");
        if( (int)me->query_skill("literate", 1) < 1 )
                return notify_fail("你暈了吧! 還是先去學點文化吧。\n");
        jing_cost = 30 + random(me->query_int()/10);
        if( query("jing", me)<jing_cost*times )
                return notify_fail("你現在太累了，領悟不了這麼多次，休息一會兒再來吧。\n");
        where = environment(me);
        switch (file_name(where))
        {
                case "/d/xiakedao/shiroom01": item = 0; break;
                case "/d/xiakedao/shiroom02": item = 1; break;
                case "/d/xiakedao/shiroom03": item = 2; break;
                case "/d/xiakedao/shiroom04": item = 3; break;
                case "/d/xiakedao/shiroom05": item = 4; break;
                case "/d/xiakedao/shiroom06": item = 5; break;
                case "/d/xiakedao/shiroom07": item = 6; break;
                case "/d/xiakedao/shiroom08": item = 7; break;
                case "/d/xiakedao/shiroom09": item = 8; break;
                case "/d/xiakedao/shiroom10": item = 9; break;
                case "/d/xiakedao/shiroom11": item = 10; break;
                case "/d/xiakedao/shiroom12": item = 11; break;
                case "/d/xiakedao/shiroom13": item = 12; break;
                case "/d/xiakedao/shiroom14": item = 13; break;
                case "/d/xiakedao/shiroom15": item = 14; break;
                case "/d/xiakedao/shiroom16": item = 15; break;
                case "/d/xiakedao/shiroom17": item = 16; break;
                case "/d/xiakedao/shiroom18": item = 17; break;
                case "/d/xiakedao/shiroom19": item = 18; break;
                case "/d/xiakedao/shiroom20": item = 19; break;
                case "/d/xiakedao/shiroom21": item = 20; break;
                case "/d/xiakedao/shiroom22": item = 21; break;
                case "/d/xiakedao/shiroom23": item = 22; break;
                case "/d/xiakedao/shiroom24": item = 23; break;
                default: break;
        }

        message_vision("$N正在鑽研石壁上的圖案和註釋。\n",me);

        // 不是互搏或太玄則要求最低等級80
        if( me->query_skill(skill_name[item], 1) < 80 ) {
                  if( item != 23 )
                        if( item != 18 ) {
                                write("你望着石壁冥思苦想了一會，發覺上面的東西對你來説太深奧了。\n");
                                return 1;
                        }
        }
        if( me->query_skill(skill_name[item], 1) >= 5900 ) {
                write("你望着石壁冥思苦想了一會，發覺上面的東西對你來説太淺薄了。\n");
                return 1;
        }
        // 辟邪劍法和葵花心法
        if( item == 4 || item == 22 ) {
                if( me->query_skill("pixie-jian", 1) >= 2500 )
                        return notify_fail("你的辟邪劍法已經無法再提高了。\n");
                if( query("gender", me) != "無性"){
                        write("可是壁上是辟邪劍法圖譜，欲練神功，必先自宮。\n");
                        return 1;
                }
        } else {
                if( !SKILL_D(skill_name[item])->valid_learn(me) )
                        return SKILL_D(skill_name[item])->valid_learn(me);
        }
        if( (int)(me->query_skill(skill_name[item], 1) *
                me->query_skill(skill_name[item],1)*81) >= query("combat_exp", me)){
                write("你對着石壁冥思苦想了一會，毫無收穫。\n");
                return 1;
        }

        learn_pot=random(query("int", me));
        if( learn_pot > 0 ) {
                // 葵花心法
                if( item == 22 ) {
                        me->improve_skill(skill_name[item], times*(random(me->query_kar())+(10+random(me->query_int()-9))/200+1));
                        success = 1;
                }
                else if( item == 4 || item == 5 ) { // 辟邪劍法 | 乾坤大挪移
                        me->improve_skill(skill_name[item], times*(random(me->query_kar())+(10+random(me->query_int()-9))/100+1));
                        success = 1;
                }
                else if( item == 23 || item == 19 ) { // 太玄功 | 小無相
                        //if( me->query_kar() >= 30 )
                        me->improve_skill(skill_name[item], times*(random(me->query_kar())+(10+random(me->query_int()-9))/100+1));
                        success = 1;
                }
                else if( me->query_skill(skill_name[item], 1) > 1000 ) {
                        me->improve_skill(skill_name[item], times*(random(me->query_kar())+(10+random(me->query_int()-9))/30+1));
                        success = 1;
                }
                else {
                        me->improve_skill(skill_name[item], times*(random(me->query_kar())+(10+random(me->query_int()-9))/10+1));
                        success = 1;
                }
//              write("你對着石壁冥思苦想了一會，似乎"+CHINESE_D->chinese(skill_name[item])+"有些心得。\n");
        }
//      else
//              write("你對着石壁冥思苦想了一會，可是成見太深，似乎沒啥心得。\n");

        if( success == 1 ) {
                me->receive_damage("jing", times*jing_cost);
                me->receive_damage("qi",times*random(query("int", me)));
                write("你對着石壁冥思苦想了"+chinese_number(times)+"回，似乎對"+CHINESE_D->chinese(skill_name[item])+"有些心得。\n");
        } else {
                me->receive_damage("jing", jing_cost);
                write("你對着石壁冥思苦想了一會，可是成見太深，似乎沒啥心得。\n");
        }
        success = 0;
        return 1;
}