# OS2dagsorden – Contribution guidelines

Thank you for your interest in contributing. It is greatly
appreciated. However, your contributions must follow the guidelines
below.

## Coding standards

All code must follow the official Drupal coding standards:
https://www.drupal.org/docs/develop/standards/coding-standards.

Your code will be run through a set of static analysis tools and
continuous integration builds to ensure compliance and project
integrity. Your code should pass these tests without raising new
issues or breaking the build. [The status of the tests will be
reported within the pull
request](https://github.com/blog/1935-see-results-from-all-pull-request-status-checks).

If you want to be notified through other means you must follow the
projects/subscribe to updates on the individual test platforms
([Scrutinizer](https://scrutinizer-ci.com/g/OS2dagsorden/os2dagsorden-2.0/).


### Local checks

To check your code locally, first install Coder Sniffer: https://www.drupal.org/node/1419988.

Then check all of the code by running

```
phpcs
```

To check only some files, add them as parameters to the `phpcs` command, e.g.

```
phpcs public_html/profiles/os2dagsorden/modules/os2dagsorden/os2dagsorden_annotator/os2dagsorden_annotator.module
```

To code you've changed before a commit, use

```
phpcs $(git diff --name-only)
```
