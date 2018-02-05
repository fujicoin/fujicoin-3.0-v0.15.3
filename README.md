Fujicoin Core integration/staging tree
=====================================

http://www.fujicoin.org

What is Fujicoin?
----------------

Fujicoin is a fork of Bitcoin that is designed to resist the monopolisation of
mining power.
 - 1 minute block targets
 - Coins are issued based on S-curve theory
 - ~10 billion total coins
 - Difficulty retargeting every block to recover from large hashrate swings
 - scrypt-N11 proof of work algorithm for ASIC resistance


For more information, as well as an immediately useable, binary version of
the Fujicoin Core software, see http://www.fujicoin.org/, or read the
[What is Fujicoin? page](http://www.fujicoin.org/what-is-fujicoin.php).

License
-------

Fujicoin Core is released under the terms of the MIT license. See [COPYING](COPYING) for more
information or see https://opensource.org/licenses/MIT.

Development Process
-------------------

The `master` branch is regularly built and tested, but is not guaranteed to be
completely stable. [Tags](https://github.com/fujicoin/fujicoin/tags) are created
regularly to indicate new official, stable release versions of Fujicoin Core.

Developers work on their own forks and submit pull requests in order to merge
changes with `master`. Due to the relatively small size of the development team,
developers also commit directly to the repo often. Anyone is allowed to contribute
though and useful pull requests will almost always be accepted given various
obvious stipulations regarding stability etc. 

The Fujicoin [slack](http://slack.fujicoin.org/) or [subreddit](https://reddit.com/r/fujicoin)
should be used to discuss complicated or controversial changes with the developers 
before working on a patch set.

Testing
-------

Fujicoin currently relies on Bitcoin Core for its testcases, and few of them are
known to work, though the software is based on fully test conforming upstream 
Bitcoin Core versions. We would be grateful to those who can help port the existing
Bitcoin Core test cases to Fujicoin such that they can be used to assure correctness.

Translations
------------
Changes to translations as well as new translations can be submitted to as pull
requests to this repo or to upstream Bitcoin Core.
