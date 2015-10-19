#include "router.h"

void parse_http_request(char* request, struct slre_cap *caps) {
  if (!slre_match("^\\s*(\\S+)\\s+(\\S+)\\s+HTTP/(\\d)\\.(\\d)",
                 request, strlen(request), caps, 4, 0) > 0) {
    printf("Error parsing [%s]\n", request);
    exit(1);
  }
}

void handle_request(char* client_message, int sock) {
  struct slre_cap caps[4], params[2];
  parse_http_request(client_message, caps);

  char *path = malloc(caps[1].len + 1);
  memcpy(path, caps[1].ptr, caps[1].len);
  path[caps[1].len] = '\0';

  if (!slre_match("^/([a-z]+)/([a-z]+)", path, strlen(path), params, 2, 0) > 0) {
    printf("Error parsing [%s]\n", path);
    exit(1);
  } else {
    char *service = malloc(params[0].len + 1);
    memcpy(service, params[0].ptr, params[0].len);
    service[params[0].len] = '\0';

    char *username = malloc(params[1].len + 1);
    memcpy(username, params[1].ptr, params[1].len);
    username[params[1].len] = '\0';
    char *image_url;


    if (strcmp(service, "instagram") == 0) {
      image_url = get_instagram_url_for(username);
    } else if (strcmp(service, "facebook") == 0) {
      image_url = get_facebook_url_for(username);
    } else if (strcmp(service, "twitter") == 0) {
      image_url = get_twitter_url_for(username);
    } else if (strcmp(service, "gravatar") == 0) {
      image_url = get_gravatar_url_for(username);
    }

    download_jpeg(image_url, sock);
  }
}
