// object.c

/* 傳回跟 ob 在同一環境或同一座標內之物件陣列, 包括 ob 本身 */
/* 此 simul_efun 對于 mud 效率有很大的影響, 若有必要, 需改寫成真正的 efun */
object *present_objects(object ob)
{
        // env 為目前物件所在的空間
        object env = environment(ob);
        
        // 沒有環境！？
        if( !env ) return allocate(0);
        
        // 如果在 map_d 系統以外直接傳回 efun:all_inventory 的值
        return all_inventory(env);
}

int same_environment(object ob1, object ob2)
{
	return objectp(ob1) && objectp(ob2) && member_array(ob2, present_objects(ob1)) != -1;
}

varargs int getoid(object ob)
{
        int id;

        if( !ob ) ob = previous_object();
        sscanf(file_name(ob), "%*s#%d", id);
        return id;
}

// Get the owner of a file.  Used by log_error() in master.c.
string file_owner(string file)
{
        string name, rest, dir;

        if( file[0] != '/' ) {
                file = "/" + file;
        }
        if( sscanf(file, "/u/%s/%s/%s", dir, name, rest) == 3 ) {
                return name;
        }
        return 0;
}

// domain_file should return the domain associated with a given file.
string domain_file(string file)
{
        string domain;

        if( sscanf(file, "/d/%s/%*s", domain) )
                return domain;

        return ROOT_UID;
}

// creator_file should return the name of the creator of a specific file.
string creator_file(string file)
{
        string *path;

        path = explode(file, "/") - ({ 0 });
        switch (path[0]) {
                case "adm":
                        if( file == SIMUL_EFUN_OB ) return "MudOS";
                        else return ROOT_UID;
                case "cmds":
                case "shadow":
                        return ROOT_UID;
                case "u":
                        if( sizeof(path) >= 3 ) return path[1];
                case "d":
                        return "Domain";
                case "f":
                        return "Fuben";
                case "maze":
                        return "Maze";
                case "quest":
                        return "Quest";
                case "task":
                        return "Task";
                case "clone":
                        return "Clone";
                case "feature":
                        return "Feature";
                case "kungfu":
                        return "Kungfu";
                case "inherit":
                        return "Inherit";
                case "template":
                        return "Template";
                default:
                        return "Unknow";
        }
}

// author_file should return the name of the author of a specific file.
string author_file(string file)
{
        string name;

        if( sscanf(file, "/u/%*s/%s/%*s", name) )
                return name;
        return ROOT_UID;
}

int living(object ob)
{
        if( query_temp("disable_input", ob) )
                return 0;

        return efun::living(ob);
}

// check the object's euid wehter is root
int is_root(mixed ob)
{
        if( stringp(ob) )
                return (SECURITY_D->get_status(ob) == "(boss)" ||
                        SECURITY_D->get_status(ob) == "(admin)");

        if( objectp(ob) ) {
                if( geteuid(ob) == ROOT_UID )
                        // Root object want to execute
                        return 1;

                return (SECURITY_D->get_status(geteuid(ob)) == "(boss)" ||
                        SECURITY_D->get_status(geteuid(ob)) == "(admin)");
        }

        return 1;
}

// Add by Doing
// simul efun:destruct
void destruct(object ob)
{
        string filename1, filename2;

        if( ob ) {
                // 遊戲系統沒有使用bind，因此為了避免call_out的BUG，做以下修改
                filename1 = file_name(ob);
                if( stringp(filename1) ) {
                        if( sscanf(filename1, "/kungfu/skill/%*s/%s", filename1) == 2 ) {
                                if( !previous_object() )
                                        return;

                                filename2 = file_name(previous_object());

                                if( !stringp(filename2) )
                                        return;

                                if( sscanf(filename2, "/cmds/%*s/%s", filename2) != 2 )
                                        return;
                        }
                }
                if( previous_object() ) ob->remove(geteuid(previous_object()));
                else ob->remove(0);
        }

        efun::destruct(ob);
}

