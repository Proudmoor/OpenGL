<?xml version="1.0" encoding="iso-8859-1"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
  <xsl:output method="html" media-type="text/html; charset=ISO-8859-1" />

  <xsl:include href="./util.xsl" />

  <xsl:template match="/">
    <html>
      <head>
        <title>OpenGL Mathematics</title>
        <meta http-equiv="Content-Language" content="en" />
        <meta http-equiv="Content-Type" content="application/xhtml+xml; charset=iso-8859-1" />
        <meta name="copyright" content="G-Truc Creation" />
        <link href="./common/style.css" rel="stylesheet" media="screen, print, embossed" type="text/css" />

        <script type="text/javascript">
          var _gaq = _gaq || [];
          _gaq.push(['_setAccount', 'UA-20182250-1']);
          _gaq.push(['_setDomainName', '.g-truc.net']);
          _gaq.push(['_trackPageview']);

          (function() {
          var ga = document.createElement('script'); ga.type = 'text/javascript'; ga.async = true;
          ga.src = ('https:' == document.location.protocol ? 'https://ssl' : 'http://www') + '.google-analytics.com/ga.js';
          var s = document.getElementsByTagName('script')[0]; s.parentNode.insertBefore(ga, s);
          })();
        </script>
      </head>
      <body>
        <table>
          <tr>
            <td class="menu">
              <xsl:apply-templates select="./glm/menu" />
            </td>
            <td class="page">
              <!--div class="title1">OpenGL Mathematics</div-->
              <div class="title1">
                <img src="./common/title.png" alt="OpenGL Mathematics" />
              </div>
              <xsl:apply-templates select="./glm/about-short" />
				<br />
				<xsl:apply-templates select="./glm/about-long" />
              <br />
              <xsl:apply-templates select="./glm/page_news/news" />
              <div class="title3">
                <xsl:value-of select="./glm/@copyright" />
                <a href="http://www.g-truc.net">G-Truc Creation</a>
              </div>
            </td>
          </tr>
        </table>
      </body>
    </html>
  </xsl:template>

  <xsl:template match="news">
    <div>
		<h3>
			<xsl:value-of select="./@date" /><xsl:text> - </xsl:text>
			<xsl:value-of select="./@title" />
		</h3>
		<div>
			<xsl:apply-templates />
		</div>
		<br />
    </div>
  </xsl:template>

</xsl:stylesheet>
