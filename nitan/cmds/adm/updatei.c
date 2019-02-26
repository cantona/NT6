// updatei.c
// by Doing

#include <ansi.h>

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        string file;
        string *opts;
        int opt_compile;
        int opt_detail;
        int opt_force;

        object env;
        object ob;
        object *obs;
        string *base;
        string *temp;
        int i;
        int k;
        int level;
        int count;

        if (! SECURITY_D->valid_grant(me, "(admin)"))
                return 0;

        seteuid(geteuid(me));

        if (! arg)
                   return notify_fail("你必須指明想編輯的繼承的根檔案路徑名。\n");

        file = 0;
        opt_compile = 0;
        opt_detail = 0;
        opt_force = 0;
        opts = explode(arg, " ");
        for (i = 0; i < sizeof(opts); i++)
        {
                switch(opts[i])
                {
                case "-c":
                        opt_compile = 1;
                        break;

                case "-d":
                        opt_detail = 1;
                        break;

                case "-f":
                        opt_force = 1;
                        break;

                default:
                        file=resolve_path(query("cwd", me),opts[i]);
                }
        }

        if (! sscanf(file, "%*s.c")) file += ".c"; 
        if (file_size(file) < 0)
                return notify_fail("沒有 " + file + " 這個檔案。\n");
        set("cwf", file, me);

        obs = filter_array(objects(), (: inherits($(file), $1) &&
                                         ! userp($1) &&
                                         ! playerp($1) &&
                                         ! clonep($1) :));
        obs -= ({ find_object(VOID_OB), find_object(TEMP_OB) });
        if (sizeof(obs) > 1024 && ! opt_force)
        {
                write("一共有 " + sizeof(obs) + " 個物件牽涉"
                      "在內，如果你決定編譯，請指明-f參數。\n");
                return 1;
        }

        if (sizeof(obs) > 100 && opt_compile)
                message_system("重新編譯所有繼承檔案，請稍候...");

        base = ({ file });
        count = 0;
        level = 0;

        while (sizeof(base))
        {
                if (! level)
                        write(HIG "編譯根文件：" + file + "，總共 " +
                              sizeof(obs) + " 個繼承文件。\n" NOR);
                else
                        write(sprintf(WHT "編譯第 %d 次繼承的 %d 個"
                                      "文件，還剩 %d 個文件。\n" NOR,
                                      level, sizeof(base), sizeof(obs)));
                temp = ({ });
                for (i = 0; i < sizeof(base); i++)
                {
                        reset_eval_cost();
                        if (opt_compile)
                        {
                                object *moves;

                                if (opt_detail) write("編譯" + base[i] + ":");

                                moves = 0;
                                if (ob = find_object(base[i]))
                                {
                                        // if a player in this room, I should move all
                                        // the objects out.
                                        if (sizeof(filter_array(deep_inventory(ob),
                                                                (: userp($1) || playerp($1) :))) > 0)
                                        {
                                                moves = all_inventory(ob);
                                                moves->move(VOID_OB, 1);
                                        }
                                        env = environment(ob);
                                        destruct(ob);
                                } else
                                {
                                        // no object, so no environment
                                        env = 0;
                                }
                
                                if (catch(ob = load_object(base[i])))
                                {
                                        write(HIR "\n編譯遇到錯誤中止。\n" NOR);
                                        return 1;
                                }

                                // compiled successfully, I should move the
                                // objects in void back, if I has been move them
                                // out from old object.
                                if (objectp(ob) && arrayp(moves))
                                        moves->move(ob, 1);

                                if (opt_detail) write("成功！\n");

                                // if the old object has environment, I should
                                // replace this object in the environment.
                                if (ob && env && (! environment(ob) || environment(ob) != env))
                                        ob->move(env);
                        } else
                        {
                                if (opt_detail)
                                        write("需要編譯" + base[i] + "。\n");
                        }
                        count++;
        
                        for (k = 0; k < sizeof(obs); k++)
                        {
                                if (member_array(base[i], inherit_list(obs[k])) != -1)
                                {
                                        temp += ({ base_name(obs[k]) + ".c" });
                                        obs[k] = 0;
                                }
                        }
                        obs -= ({ 0 });
                }

                level++;
                base = temp;
        }

        if (count > 0)
                write(HIC "總共有" + HIW + count + HIC "個檔案" +
                      (opt_compile ? "被成功編譯！\n" NOR : "需要編譯。\n" NOR));
        else
                write(HIC "沒有編譯任何檔案需要編譯。\n" NOR);

        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : updatei <檔案名> [-c] [-d] [-f]
 
這個指令可以更新某個檔案和所有繼承該檔案的物件，不過那些複製
出來的物件不會更新。比如你編譯了/feature/message，則繼承該文
件的/inherit/char/char和間接繼承的/inherit/char/npc 都會被重
新編譯。如果一個物件是玩家對象，則不會被編譯。

如果不指明參數-c，則系統只是列出需要編譯那些檔案。如果指明瞭
參數-c，則編譯範圍在1024 個文件內,如果指明瞭參數-d，則採用詳
細模式列出所有需要編譯的檔案。如果指明瞭-f則編譯所有對象，否
則超過了1024個文件系統就不會進行編譯。
HELP );
    return 1;
}