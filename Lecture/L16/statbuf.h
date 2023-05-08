/* Metadata returned by the stat and fstat functions    */
struct stat {
    dev_t       st_dev;     /* Devices */
    ino_t       st_ino;     /* inode */
    mode_t      st_mode;    /* Protection and file type */
    nlink_t     st_nlink;   /* Number of hard links */
    uid_t       st_uid;     /* User ID of owner */
    gid_t       st_gid;
    dev_t       st_rder;    /* Device type (if inodes device) */
    off_t       st_size;    /* Totle size, in bytes */
    unsigned long st_blksize;   /* Block size for filesystem T/O */
    unsigned long st_blocks;/* Number of blocks allocated */
    time_t      st_atime;
    time_t      st_mtime;
    time_t      st_ctime;
};
