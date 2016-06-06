/*
 * $Id$
 *
 * Copyright (c) 2016, Juniper Networks, Inc.
 * All rights reserved.
 * This SOFTWARE is licensed under the LICENSE provided in the
 * ../Copyright file. By downloading, installing, copying, or otherwise
 * using the SOFTWARE, you agree to be bound by the terms of that
 * LICENSE.
 *
 * Phil Shafer (phil@) June 2016
 */

#ifndef LIBSLAX_XI_SOURCE_H
#define LIBSLAX_XI_SOURCE_H

typedef uint8_t xi_node_type_t;	/* Type of node (XI_TYPE_*) */
typedef uint32_t xi_node_id_t;	/* Node identifier (index) */
typedef uint16_t xi_name_id_t;	/* Element name identifier (index) */
typedef uint16_t xi_ns_id_t;	/* Namespace identifier (index) */
typedef uint8_t xi_depth_t;	/* Depth in the hierarchy */
typedef off_t xi_offset_t;	/* Offset in file or buffer */
typedef uint32_t xi_source_flags_t; /* Flags for parser */

/* Type of XML nodes */
#define XI_TYPE_NONE	0	/* Unknown type */
#define XI_TYPE_EOF	1	/* End of file */
#define XI_TYPE_FAIL	2	/* Failure mode */
#define XI_TYPE_ROOT	3	/* Root node (container); not "root element" */
#define XI_TYPE_TEXT	4	/* Text content */
#define XI_TYPE_OPEN	5	/* Open tag */
#define XI_TYPE_CLOSE	6	/* Close tag */
#define XI_TYPE_EMPTY	7	/* Empty tag */
#define XI_TYPE_PI	8	/* Processing instruction */
#define XI_TYPE_DTD	9	/* <!DTD> nonsense */
#define XI_TYPE_COMMENT	10	/* Comment */
#define XI_TYPE_ATTR	11	/* XML attribute */
#define XI_TYPE_NS	12	/* XML namespace */
#define XI_TYPE_SKIP	13	/* Skip/ignored input */
#define XI_TYPE_CDATA	14	/* Cdata (<![CDATA[ ]]>) */

#define XI_TYPE_ELT	XI_TYPE_OPEN

/*
 * Parser source object
 *
 * Note that we return pointers directly into our buffer.
 */
typedef struct xi_source_s {
    int xps_fd;			/* File being read */
    char *xps_filename;		/* Filename */
    unsigned xps_lineno;	/* Line number of input */
    unsigned xps_offset;	/* Offset in the file */
    xi_source_flags_t xps_flags; /* Flags for this source */
    char *xps_bufp;		/* Input buffer */
    char *xps_curp;		/* Current data point */
    unsigned xps_len;		/* Number of bytes in the input buffer */
    unsigned xps_size;		/* Size of the input buffer (max) */
    xi_node_type_t xps_last;	/* Type of last token returned */
} xi_source_t;

/* Flags for ps_flags: */
#define XPSF_MMAP_INPUT	(1<<0)	/* File is mmap'd */
#define XPSF_IGNORE_WS	(1<<1)	/* Ignore whitespace-only mixed content */
#define XPSF_NO_READ	(1<<2)	/* Don't read() on this fd */
#define XPSF_EOF_SEEN	(1<<3)	/* EOF has been seen; read should fail */
#define XPSF_READ_ALL	(1<<4)	/* File is read completely into memory */
#define XPSF_CLOSE_FD	(1<<5)	/* Close fd when cleaning up */
#define XPSF_TRIM_WS	(1<<6)	/* Trim whitespace from data */
#define XPSF_VALIDATE	(1<<7)	/* Validate input */
#define XPSF_LINE_NO	(1<<8)	/* Track line numbers for input */
#define XPSF_IGNORE_COMMENTS (1<<9) /* Discard comments */
#define XPSF_IGNORE_DTD (1<<10) /* Discard DTDs */

xi_source_t *
xi_source_create (int fd, xi_source_flags_t flags);

xi_source_t *
xi_source_open (const char *path, xi_source_flags_t flags);

void
xi_source_destroy (xi_source_t *srcp);

xi_node_type_t
xi_source_next_token (xi_source_t *srcp, char **datap, char **restp);

size_t
xi_source_unescape (xi_source_t *srcp, char *start, unsigned len);

void
xi_source_failure (xi_source_t *srcp, int errnum, const char *fmt, ...);

#endif /* LIBSLAX_XI_SOURCE_H */
